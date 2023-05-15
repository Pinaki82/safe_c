// Last Change: 2023-05-14  Sunday: 10:53:23 PM
/*
   Licence: Boost Software License, https://www.boost.org/users/license.html
*/

#ifndef  __SF_C_H__
#define  __SF_C_H__


//MACRO, global variables, etc..
#define MAXBUFF 1E+5f   // integer 1x10^+5 = 1 M. the max no. chars that will be dealt with.

#ifndef BUFSIZ // needed by sf_getchar()
  #define BUFSIZ 1024
#endif

#define DICT_LEN 256 // needed by create_delim_dict()

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>  // for size_t, sf_strchr()
#include <string.h>
// https://learn.microsoft.com/en-us/cpp/c-runtime-library/file-constants?view=msvc-170
#include <fcntl.h>
#include <stdarg.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <stdint.h> // for uint8_t



#ifdef _WIN32
  #include  <windows.h>
#else
  #include <ncurses.h>
#endif






#ifdef __cplusplus
extern "C" {
#endif

void *sf_memmove(void *destn, const void *src, unsigned int n);

// an alternative function to strlen() that checks buffer size as an argument
size_t sf_strlen(const char *str, size_t max_len);

// https://www.tutorialspoint.com/c_standard_library/c_function_strncpy.htm

// an alternative function to strcpy() that checks buffer size as an argument
void sf_strcpy(char *dest, const char *src, size_t size);  //size=sizeof(dest). Increase size at declaration.

// an alternative function to strncpy() that checks buffer size as an argument
void sf_strncpy(char *dest, const char *src, size_t n);

// an alternative function to gets() that checks buffer size as an argument
char *sf_gets(char *str, int size, FILE *stream);

// an alternative function to scanf() that checks buffer size as an argument
int sf_scanf(char *format, void *arg, size_t max_len);

// an alternative function to getchar(() that handles input more appropriately
int sf_getchar(void);

// an alternative function to strcat() that handles input more appropriately
char *sf_strcat(char *dest, const char *src, size_t dest_size);

// an alternative function to sprintf() that handles input more appropriately
int sf_sprintf(char *buffer, const char *format, ...);

// an alternative function to atoi() that checks for invalid input
// if(sf_atoi(str, &result) == false) // invalid output = false
bool sf_atoi(const char *str, int *result);

// A safe version of `vsnprintf()` which ensures that the destination buffer is not null and its size is at least 1.
int sf_vsnprintf(char *buf, size_t size, const char *fmt, va_list args);

size_t bard_vsnprintf(char *buffer, size_t size, const char *format, va_list args);

// A safe version of `vsprintf()` which ensures that the destination buffer is not null and its size is at least 1.
int sf_vsprintf(char *dest, size_t dest_size, const char *format, va_list args);

// an alternative function to sscanf() that checks buffer size taken from an argument and checks for NULL ptrs
int sf_sscanf(const char *restrict str, const char *restrict format, ...);

// function: holds the screen before the text disappears
void sf_holdscr(void);

// clears the screen safely
#ifdef _WIN32
void sf_cls(void);
#else
void sf_cls(void);
#endif




#define sf_assert(expr) \
  do { \
    if (!(expr)) { \
      fprintf(stderr, "Assertion failed: %s\n", #expr); \
      errno = EFAULT; \
      return -1; \
    } \
  } while (0)


void sf_fflush_out(FILE *stream);

int sf_vfprintf(FILE *stream, const char *format, va_list ap);


#ifdef _MSC_VER
#define strtok(str, delim) _strtok_s(str, delim, NULL)
#else
#define strtok(str, delim) strtok_r(str, delim, NULL)
#endif


void sf_puts(const char *s, FILE *stream);

int sf_putc(int c, FILE *stream);

int sf_putchar(int c);

int sf_getc(FILE *stream, char *buffer, size_t buflen);

void *sf_memcpy(void *to, const void *from, size_t numBytes);

char *strdup(const char *s);

char *strndup(const char *s, size_t n);

char *sf_fgets(char *s, int size, FILE *stream);

char *sf_strtok(char *str, const char *delim, size_t max_len);

errno_t sf_memset(
        void *dest,
        size_t destSize,
        int value,
        size_t count
);

int sf_vfscanf(FILE *stream, const char *format, va_list arg);

int sf_fscanf(FILE *fp, const char *format, ...);

int sf_snprintf(char *dest, size_t dest_size, const char *format, ...);

char *sf_strchr(const char *str, int ch);

char *sf_strncat(char *dest, const char *src, size_t n);

#ifdef __cplusplus
}
#endif

#endif  /* __SF_C_H__ */

/* Non-global prototypes */

/* A backup function for snprintf() that uses another safe version of vsnprintf(). */
int backup_4_safe_vsnprintf(char *dest, size_t dest_size, const char *format, va_list args);

int is_valid_input_char(char c);

int *create_delim_dict(const char *delim, size_t max_len);

/* Fn definitions start here */

void *sf_memmove(void *destn, const void *src, unsigned int n) {
  n = n + 1;
  char *pDest = (char *)destn;
  const char *pSrc = (const char *)src;

  if(!n) {
    fprintf(stderr, "Invalid memmove() call: !n\n");
    return NULL;
  }

  if(src == NULL) {
    fprintf(stderr, "Invalid memmove() call: src == NULL\n");
    return NULL;
  }

  if(destn == NULL) {
    fprintf(stderr, "Invalid destination buffer\n");
    return NULL;
  }

  // Check if source buffer overlaps with destination buffer
  if(pSrc < pDest && pSrc + n > pDest) {
    // Copy backwards to avoid overwriting source buffer
    pSrc += n;
    pDest += n;

    for(unsigned int i = 0; i < n; i++) {
      *(--pDest) = *(--pSrc);
    }
  }

  else { // if the current position in the destination buffer (pDest + i) is greater than or equal to the end of the destination buffer ((char*)destn + n). If it is, an error message is printed and NULL is returned.
    for(unsigned int i = 0; i < n; i++) {
      if((pDest + i) >= ((char *)destn + n)) {
        fprintf(stderr, "Destination buffer is not big enough\n");
        return NULL;
      }

      *(pDest + i) = *(pSrc + i);
    }
  }

  return destn;
}

// an alternative function to strlen() that checks buffer size as an argument
// Based on // https://stackoverflow.com/questions/5935413/is-there-a-safe-version-of-strlen
// Minor changes has been made with the help of ChatGPT and efforts on my part.
/* // https://stackoverflow.com/questions/32599064/is-strlen-unsafe-when-getting-the-last-char-in-a-string-in-c
   // Now, the following will be handled perfectly.
  size_t max_len = 15;
  size_t len;
  char *str = (char *)NULL;
  len = sf_strlen2(str, max_len);  // no segmentation fault -- no crash
*/
size_t sf_strlen(const char *str, size_t max_len) {
  if(str == NULL) {
    // handle null string case
    fprintf(stderr, "%s", "null string!\n");
    return 0;
  }

  else if(max_len == 0) {
    // handle zero length case
    return 0;
  }

  else {
    const char *end = (const char *)memchr(str, '\0', max_len);

    if(end == NULL) {
      // string is longer than max_len
      return max_len - 1;
    }

    else {
      return (size_t)(end - str);
    }
  }
}

// an alternative function to strcpy() that checks buffer size as an argument
void sf_strcpy(char *dest, const char *src, size_t size) { //size=sizeof(dest). Increase size at declaration. // FIXME: problematic fn
  /*
    -------------------------------------------------------------------
    dest: a pointer to the destination character array where the copied string will be stored
    src: a pointer to the source string that will be copied
    size: the size of the destination character array, including space for the null terminator
    This function takes aforementioned three arguments.

    The purpose of this function is to copy
    the contents of the src string
    into the dest character array.
    It does this by iterating through each character
    in the src string and copying it over to the
    corresponding index in the dest array.
    The loop stops when either the end of the src string is reached
    or the dest array is full (i.e. i is equal to size - 1).
    -------------------------------------------------------------------
  */
  size = size + 1;
  size_t i;

  for(i = 0; i < size - 1 && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }

  dest[i] = '\0';
}

// an alternative function to strncpy() that checks buffer size as an argument
void sf_strncpy(char *dest, const char *src, size_t n) {
  size_t i;

  for(i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }

  for(; i < n; i++) {
    dest[i] = '\0';
  }
}

// an alternative function to gets() that checks buffer size as an argument
char *sf_gets(char *str, int size, FILE *stream) { //size=sizeof(dest).
  if(fgets(str, size, stream) == NULL) { //fgets() returns NULL when the end of the file is reached
    return NULL;
  }

  size_t len = sf_strlen(str, MAXBUFF); //strlen() returns the length of the string in bytes

  if(len > 0 && str[len - 1] == '\n') { //if the last character of the string is a newline
    str[len - 1] = '\0'; //then remove it
  }

  return str; //return the string in the buffer
} // you can also do #define gets sf_gets in your source file.

// You won't be able to use strcpy,
// strncpy, and gets from the compiler provided library anymore
// because they are now macros and they are re-defined here.


int sf_scanf(char *format, void *arg, size_t max_len) {
  // Read a line of input from stdin
  char *line = (char *)malloc(max_len + 1);

  if(!fgets(line, (int)(max_len + 1), stdin)) {
    // Error reading input
    free(line);
    return EOF;
  }

  // Check if input exceeded max length
  if(strlen(line) == max_len && line[max_len - 1] != '\n') {
    // Input exceeded max length
    fprintf(stderr, "Input exceeded maximum length of %zu characters\n", max_len);
    free(line);
    return EOF;
  }

  // Parse the input using sscanf()
  int result = sf_sscanf(line, format, arg); /* FIXME: sscanf() insecure */ // SEGFAULT: sf_sscanf. GDB traceback to sf_sscanf
  free(line);
  return result;
}

// an alternative function to sscanf() that checks buffer size taken from an argument and checks for NULL ptrs
int sf_sscanf(const char *restrict str, const char *restrict format, ...) { // FIXME: problematic fn
  if(str == NULL || format == NULL) {
    // Invalid input
    return EOF;
  }

  // Get the length of the input string
  size_t len = strlen(str);
  // Allocate memory for a copy of the string
  char *str_copy = (char *)malloc(len + 1);

  if(!str_copy) {
    // Failed to allocate memory
    return EOF;
  }

  // Copy the input string
  sf_strncpy(str_copy, str, len + 1);
  str_copy[len] = '\0';
  // Parse the input using sscanf()
  va_list args;
  va_start(args, format);
  int result = vsscanf(str_copy, format, args); /* INSECURE: vsscanf() insecure */
  va_end(args);
  // Free the memory used by the string copy
  free(str_copy);
  return result;
}


// an alternative function to getchar() that handles input more appropriately
int sf_getchar(void) {
  static char buf[BUFSIZ];
  static char *bufp = buf;
  static int n = 0;

  if(n == 0) {
    n = read(0, buf, sizeof buf);
    bufp = buf;
  }

  if(--n >= 0) {
    return *bufp++;
  }

  return EOF;
}

/*
  #include <stdlib.h> // for NULL
  #include <stdio.h>  // for fprintf
  #include <string.h> // for strlen

  The function sf_strcat is an implementation of the strcat function that appends a string to the end of another string, with additional checks to ensure that the operation is performed safely. Here is how the function works:

  It takes three parameters: the destination string dest, the source string src, and the size of the destination buffer dest_size.

  It first gets the length of the destination string using strlen(dest) and stores it in dest_len.

  It then gets the length of the source string using strlen(src) and stores it in src_len.

  The function then checks if there is enough space in the destination buffer to append the source string. If there isn't enough space, the function prints an error message to stderr and returns NULL. This step prevents buffer overflows.

  The function then gets a pointer to the end of the destination string using a loop. The loop starts at the beginning of the destination string and iterates until it finds the null terminator at the end of the string or reaches the end of the buffer.

  The function then copies the source string to the end of the destination string using another loop. The loop starts at the beginning of the source string and iterates until it finds the null terminator at the end of the string or reaches the end of the buffer.

  After the source string has been appended to the destination string, the function adds a null terminator at the end of the string to terminate it properly.

  If the destination buffer is too small to hold the null terminator, the function adds a null terminator at the end of the buffer to prevent buffer overflow.

  Finally, the function returns a pointer to the destination string.
*/

// an alternative function to strcat() that handles input more appropriately
char *sf_strcat(char *dest, const char *src, size_t dest_size) {
  // Get the length of the destination string
  size_t dest_len = strlen(dest);
  // Get the length of the source string
  size_t src_len = strlen(src);

  // Check if there is enough space in the destination buffer to append the source string
  if(dest_size - (dest_len + 1) <= src_len) {
    // If there isn't enough space, print an error message to stderr and return NULL
    fprintf(stderr, "safe_strcat: destination buffer is too small\n");
    return NULL; // Not enough space in destination buffer
  }

  // Get a pointer to the end of the destination string
  char *dest_end = dest;

  while(*dest_end != '\0' && dest_end - dest < (ptrdiff_t)dest_size) {
    // Find the end of the destination string
    ++dest_end; // move to the next character in the destination string
  }

  // Copy the source string to the end of the destination string
  while(*src != '\0' && dest_end - dest < (ptrdiff_t)dest_size - 1) {
    *dest_end++ = *src++;
  }

  // Add a null terminator to the end of the string
  if(dest_end - dest < (ptrdiff_t)dest_size) {
    *dest_end = '\0';
  }

  else {
    // If the destination buffer is too small and the null terminator could not be added, add a null terminator at the end of the buffer to prevent buffer overflow.
    // buffer overflow detected!
    dest[dest_size - 1] = '\0';
  }

  // Return a pointer to the destination string
  return dest;
}

// an alternative function to sprintf() that handles input more appropriately
int sf_sprintf(char *buffer, const char *format, ...) {
  if(buffer == NULL || format == NULL) {
    fprintf(stderr, "sf_sprintf: invalid input\n");
    return -1;
  }

  size_t buffer_len = strnlen(buffer, BUFSIZ);

  if(buffer_len == BUFSIZ) {
    fprintf(stderr, "sf_sprintf: buffer is too small\n");
    return -1;
  }

  va_list args;
  va_start(args, format);
  int result = vsnprintf(buffer + buffer_len, BUFSIZ - buffer_len, format, args);
  va_end(args);

  if((size_t)result < 0 || (size_t)result >= BUFSIZ - buffer_len) {
    fprintf(stderr, "sf_sprintf: buffer overflow\n");
    return -1;
  }

  return (int)((int)buffer_len + result);
}

// clears the screen safely
#ifdef _WIN32  // For Windows
void sf_cls(void) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD coordScreen = { 0, 0 };    // home for the cursor
  DWORD cCharsWritten;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD dwConSize;

  // Get the number of character cells in the current buffer
  if(!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
    return;
  }

  dwConSize = (DWORD)csbi.dwSize.X * (DWORD)csbi.dwSize.Y;

  // Fill the entire screen with spaces
  if(!FillConsoleOutputCharacter(hConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten)) {
    return;
  }

  // Move the cursor to the home position
  SetConsoleCursorPosition(hConsole, coordScreen);
}
#else  // For Linux and Mac
void sf_cls(void) {
  initscr();
  clear();
  refresh();
  endwin();
}
#endif

// an alternative function to atoi() that checks for invalid input
// if(sf_atoi(str, &result) == false) // invalid output = false
bool sf_atoi(const char *str, int *result) {
  long long_val;
  char *endptr;
  long_val = strtol(str, &endptr, 10);

  // Check for invalid input or underflow/overflow
  if(*endptr != '\0' || long_val < INT_MIN || long_val > INT_MAX) {
    return false;
  }

  *result = (int)long_val;
  return true;
}

/*
   sf_vsnprintf - Safely format a variable argument list to a string buffer with size checking.

   This function formats the variable argument list according to the provided format string and writes the resulting string
   to the provided destination buffer, ensuring that the buffer is not overflowed. The size of the destination buffer
   must be specified, and the function returns the number of characters that would have been written if there were enough
   space. If an error occurs, the function returns a negative value.

   Parameters:
       dest - A pointer to the destination buffer to which the formatted string will be written.
       dest_size - The size of the destination buffer, in bytes.
       format - A format string that specifies how the variable argument list should be formatted.
       args - A variable argument list that contains the values to be formatted.

   Returns:
       The number of characters that would have been written if there were enough space, excluding the null terminating
       character. If an error occurs, a negative value is returned.

    Refer to https://en.cppreference.com/w/c/io/vfprintf for more info.
*/

// A safe version of `vsnprintf()` which ensures that the destination buffer is not null and its size is at least 1.
int sf_vsnprintf(char *buf, size_t size, const char *fmt, va_list args) {
  char *buf_end = buf + size - 1; // leave space for null terminator
  char *buf_ptr = buf;
  const char *fmt_ptr = fmt;

  while(*fmt_ptr && buf_ptr < buf_end) {
    if(*fmt_ptr != '%') {
      *buf_ptr++ = *fmt_ptr++; // SEGFAULT:
      continue;
    }

    fmt_ptr++;

    if(*fmt_ptr == '%') {
      *buf_ptr++ = '%';
      fmt_ptr++;
      continue;
    }

    if(*fmt_ptr == '\0') {
      break;
    }

    if(*fmt_ptr == 'd') {
      int value = va_arg(args, int);
      char value_buf[13];
      char *value_ptr = value_buf + sizeof(value_buf) - 1; // start at end of buffer

      if(value < 0) {
        *buf_ptr++ = '-';
        value = -value;
      }

      // convert integer to string, starting from end of buffer
      do {
        *value_ptr-- = value % 10 + '0';
        value /= 10;
      } while(value > 0);

      // copy string to output buffer
      while(++value_ptr < value_buf + sizeof(value_buf) && buf_ptr < buf_end) {
        *buf_ptr++ = *value_ptr;
      }

      fmt_ptr++;
    }

    else if(*fmt_ptr == 's') {
      char *value = va_arg(args, char *);
      size_t remaining_space = (size_t)(buf_end - buf_ptr + 1); // +1 for null terminator

      if(value == NULL) {
        value = "(null)";
      }

      size_t value_len = strnlen(value, remaining_space); // max len should be remaining_space
      sf_memmove(buf_ptr, value, value_len);
      buf_ptr += value_len;
      fmt_ptr++;
    }

    else if(*fmt_ptr == 'x') {
      unsigned int value = va_arg(args, unsigned int);
      char value_buf[8];
      char *value_ptr = value_buf;

      do {
        unsigned int nibble = value & 0xf;
        *value_ptr++ = (char)(nibble + (nibble < 10 ? '0' : 'a' - 10));
        value >>= 4;
      } while(value > 0 && value_ptr < value_buf + sizeof(value_buf));

      while(value_ptr > value_buf && buf_ptr < buf_end) {
        *buf_ptr++ = *--value_ptr; // SEGFAULT: segfault
      }

      fmt_ptr++;
    }

    else {
      break;
    }
  }

  *buf_ptr = '\0';
  return (int)(buf_ptr - buf);
}

size_t bard_vsnprintf(char *buffer, size_t size, const char *format, va_list args) {
  size_t written = 0;
  char buf[BUFSIZ] = "";
  unsigned int u = '\0';
  size_t len = '\0';

  if(buffer == NULL) {
    fprintf(stderr, "Error: buffer is NULL. fn vsnprintf. \n");
    return (size_t)(-1);
  }

  if(size == 0) {
    fprintf(stderr, "Error: size is 0. fn vsnprintf. \n");
    return (size_t)(-1);
  }

  while(*format) {
    if(*format == '%') {
      format++;

      switch(*format) {
        case 'c':
          if(written >= size) {
            break;
          }

          buffer[written++] = va_arg(args, int);
          break;

        case 's': {
            char *s = va_arg(args, char *);
            size_t len = strlen(s);

            if(written + len > size) {
              len = size - written;
            }

            sf_memcpy(buffer + written, s, len + 1);
            written += len;
            break;
          }

        case '%':
          if(written >= size) {
            break;
          }

          buffer[written++] = '%';
          break;

        case 'd':
          if(written >= size) {
            break;
          }

          int i = va_arg(args, int);
          snprintf(buf, sizeof(buf), "%d", i);
          len = strlen(buf);

          if(written + len > size) {
            len = size - written;
          }

          sf_memcpy(buffer + written, buf, len + 1);
          written += len;
          break;

        case 'u':
          if(written >= size) {
            break;
          }

          u = va_arg(args, unsigned int);
          snprintf(buf, sizeof(buf), "%u", u);
          len = strlen(buf);

          if(written + len > size) {
            len = size - written;
          }

          sf_memcpy(buffer + written, buf, len + 1);
          written += len;
          break;

        case 'x':
          if(written >= size) {
            break;
          }

          u = va_arg(args, unsigned int);
          snprintf(buf, sizeof(buf), "%x", u);
          len = strlen(buf);

          if(written + len > size) {
            len = size - written;
          }

          sf_memcpy(buffer + written, buf, len + 1);
          written += len;
          break;

        case 'X':
          if(written >= size) {
            break;
          }

          u = va_arg(args, unsigned int);
          snprintf(buf, sizeof(buf), "%X", u);
          len = strlen(buf);

          if(written + len > size) {
            len = size - written;
          }

          sf_memcpy(buffer + written, buf, len + 1);
          written += len;
          break;

        case 'f':
          if(written >= size) {
            break;
          }

          double d = va_arg(args, double);
          snprintf(buf, sizeof(buf), "%f", d);
          len = strlen(buf);

          if(written + len > size) {
            len = size - written;
          }

          sf_memcpy(buffer + written, buf, len + 1);
          written += len;
          break;

        case 'g':
          if(written >= size) {
            break;
          }

          snprintf(buf, sizeof(buf), "%g", d);
          len = strlen(buf);

          if(written + len > size) {
            len = size - written;
          }

          sf_memcpy(buffer + written, buf, len + 1);
          written += len;
          break;

        default:
          // Unknown format specifier.
          fprintf(stderr, "Error: unknown format specifier. fn vsnprintf. \n");
          return (size_t)(-1);
      }
    }

    else {
      if(written >= size) {
        break;
      }

      buffer[written++] = *format;
    }

    format++;
  }

  buffer[written] = '\0';
  return written;
}



/*
   sf_vsprintf - Safely format a variable argument list to a string buffer with size checking.

   This function formats the variable argument list according to the provided format string and writes the resulting string
   to the provided destination buffer, ensuring that the buffer is not overflowed. The size of the destination buffer
   must be specified, and the function returns the number of characters that would have been written if there were enough
   space. If an error occurs, the function returns a negative value.

   Parameters:
       dest - A pointer to the destination buffer to which the formatted string will be written.
       dest_size - The size of the destination buffer, in bytes.
       format - A format string that specifies how the variable argument list should be formatted.
       args - A variable argument list that contains the values to be formatted.

   Returns:
       The number of characters that would have been written if there were enough space, excluding the null terminating
       character. If an error occurs, a negative value is returned.
*/

// A safe version of `vsprintf()` which ensures that the destination buffer is not null and its size is at least 1.
int sf_vsprintf(char *dest, size_t dest_size, const char *format, va_list args) {
  return (int)bard_vsnprintf(dest, dest_size, format, args); // BUG: bard_vsnprintf
}

int backup_4_safe_vsnprintf(char *dest, size_t dest_size, const char *format, va_list args) {
  int len = bard_vsnprintf(dest, dest_size, format, args);
  dest[dest_size - 1] = '\0'; // Null-terminate the string
  return len;
}

int sf_snprintf(char *dest, size_t dest_size, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int len = backup_4_safe_vsnprintf(dest, dest_size, format, args);
  va_end(args);
  return len;
}

// function: holds the screen before the text disappears
void sf_holdscr(void) {
#ifdef _WIN32
  system("pause >nul"); // pause >nul redirects the output of the pause command to nul to suppress the "Press any key to continue . . ." message.
#else
  /* prints a message to the console, flushes the buffer, and then reads a single character from the user input without echoing it to the terminal using the read command. Finally, it prints a newline character to ensure the cursor is on a new line before continuing. */
  printf("Press any key to continue...");
  fflush(stdout);
  system("read -rsn1"); // Linux. command explanation: `read` was used to read from stdin, `-p` means that the user will be prompted for input.  // https://unix.stackexchange.com/questions/293940/how-can-i-make-press-any-key-to-continue
  printf("\n");
#endif
}

void sf_fflush_out(FILE *stream) {
  /* TODO: check whether the stream is stdin. If so, return error. */
  fflush(stream);
}


int sf_vfprintf(FILE *stream, const char *format, va_list ap) {
  // Check for a null file pointer
  if(!stream) {
    return -1;
  }

  // Call vfprintf() with the given arguments
  return vfprintf(stream, format, ap);
}

void sf_puts(const char *s, FILE *stream) {
  size_t len = sf_strlen(s, MAXBUFF);
  char *sanitized_str = (char *)malloc((len + 1) * sizeof(char));

  if(sanitized_str == NULL) {
    perror("Error: memory allocation failed");
    exit(EXIT_FAILURE);
  }

  // Copy the string to sanitized_str and sanitize it
  sf_strncpy(sanitized_str, s, (len + 1));
  sanitized_str[len + 1] = '\0';

  for(size_t i = 0; i < (len + 1); i++) {
    if(!isprint(sanitized_str[i])) {
      sanitized_str[i] = ' ';
    }
  }

  fprintf(stream, "%s\n", sanitized_str);
  free(sanitized_str);
}

int sf_putc(int c, FILE *stream) {
  if(!isprint(c)) {
    fprintf(stderr, "Error: Non-printable character detected in input.\n");
    return EOF;
  }

  return fputc(c, stream);
}

int sf_putchar(int c) {
  if(!isprint(c) || c == '\n' || c == '\r' || c == '\t') {
    return EOF;  // reject non-printable characters and control characters
  }

  return putchar(c);  // safe to write to stdout
}

int is_valid_input_char(char c) {
  return isprint((unsigned char) c);
}

int sf_getc(FILE *stream, char *buffer, size_t buflen) {
  if(!buffer || buflen == 0) {
    return EOF;
  }

  int c = getc(stream);

  if(c == EOF) {
    buffer[0] = '\0';
    return EOF;
  }

  if(is_valid_input_char((char)c)) {
    buffer[0] = (char) c;
    buffer[1] = '\0';
    return c;
  }

  buffer[0] = '\0';
  return sf_getc(stream, buffer, buflen);
}

void *sf_memcpy(void *to, const void *from, size_t numBytes) {
  return sf_memmove(to, from, (uint32_t)numBytes);
}

/* https://stackoverflow.com/questions/46013382/c-strndup-implicit-declaration */

char *strdup(const char *s) {
  size_t size = strlen(s) + 1;
  char *p;
  p = (char *)malloc((size_t)(size) * sizeof(char));

  if(p == NULL) {
    fprintf(stderr, "\ndynamic memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  if(p != NULL) {
    sf_memmove(p, s, (uint32_t)(size + 1));
  }

  else {
    free(p);
    p = NULL;
  }

  return p;
}

char *strndup(const char *s, size_t n) {
  char *p;
  size_t n1;

  for(n1 = 0; n1 < n && s[n1] != '\0'; n1++) {
    continue;
  }

  p = (char *)malloc((size_t)(n + 1) * sizeof(char));

  if(p == NULL) {
    fprintf(stderr, "\ndynamic memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  if(p != NULL) {
    sf_memmove(p, s, (uint32_t)(n1 + 1));
    p[n1] = '\0';
  }

  else {
    free(p);
    p = NULL;
  }

  return p;
}

char *sf_fgets(char *s, int size, FILE *stream) {
  if(size <= 0) {
    fprintf(stderr, "Error: Invalid buffer size.\n");
    return NULL;
  }

  char *ret = fgets(s, size, stream);

  if(ret == NULL) {
    return ret;
  }

  // Remove the newline character at the end, if present
  size_t len = strlen(s);

  if(len > 0 && s[len - 1] == '\n') {
    s[len - 1] = '\0';
  }

  // Sanitize the string by replacing non-printable characters with spaces
  for(size_t i = 0; i < len; i++) {
    if(!isprint(s[i])) {
      s[i] = ' ';
    }
  }

  return ret;
}

errno_t sf_memset(
        void *dest,
        size_t destSize,
        int value,
        size_t count
) {
  if(dest == NULL || destSize == 0 || count > destSize) {
    return EINVAL;
  }

  volatile unsigned char *p = (volatile unsigned char *)dest;

  while(count--) {
    *p++ = (unsigned char)value;
  }

  return 0;
}

int *create_delim_dict(const char *delim, size_t max_len) {
  int *d = (int *)malloc(sizeof(int) * DICT_LEN);

  if(!d) {
    return NULL;
  }

  for(int j = 0; j < DICT_LEN; j++) { // initialisation: fill the allocated memory with zeros before using it
    *(d + j) = 0; // initialize the allocated array with zeros
  }

  sf_memset((void *)d, sizeof(int)*DICT_LEN, 0, sizeof(int)*DICT_LEN);
  int i = 0;

  for(i = 0; i < (int)sf_strlen(delim, max_len); i++) {
    d[(unsigned char)delim[i]] = 1;
  }

  return d;
}

char *sf_strtok(char *str, const char *delim, size_t max_len) {
  /*
    //https://stackoverflow.com/questions/28931379/implementation-of-strtok-function
    //https://github.com/kohn1001/mystrtok/blob/master/strtok.c
  */
  static char *last_token = NULL, *to_free = NULL;
  int *deli_dict = create_delim_dict(delim, max_len);

  if(!deli_dict || max_len == 0) {
    free(to_free);
    to_free = NULL;
    return NULL;
  }

  if(str) {
    last_token = (char *)malloc(max_len + 1);

    if(!last_token) {
      free(deli_dict);
      deli_dict = NULL;
      return NULL;
    }

    to_free = last_token;
    sf_strncpy(last_token, str, max_len); /* FIXME: strncpy(). insecure function */
    last_token[max_len] = '\0';
  }

  if(!last_token) {
    free(deli_dict);
    deli_dict = NULL;
    return NULL;
  }

  while(last_token && deli_dict[(unsigned char)*last_token] && *last_token != '\0') {
    last_token++;
  }

  if(!last_token || *last_token == '\0') {
    free(deli_dict);
    deli_dict = NULL;
    free(to_free);
    to_free = NULL;
    return NULL;
  }

  str = last_token;

  while(last_token && *last_token != '\0' && !deli_dict[(unsigned char)*last_token]) {
    last_token++;
  }

  if(last_token && *last_token != '\0') {
    *last_token++ = '\0';
  }

  free(deli_dict);
  deli_dict = NULL;
  return (char *)str;
}

int sf_vfscanf(FILE *stream, const char *format, va_list arg) {
  /*
    - The function first formats the input string using vsnprintf() and stores it in a buffer.
    - It then checks for buffer overflow by comparing the length of the formatted string with the size of the buffer.
    - It also checks for null bytes by searching for the first null byte in the buffer.
    - Finally, it calls vfscanf() to read input from the stream and checks if the file position indicator is within bounds.
  */
  char buffer[BUFSIZ];
  int n = bard_vsnprintf(buffer, BUFSIZ - 1, format, arg);

  if(n < 0 || n >= BUFSIZ) {
    return EOF;
  }

  if(strchr(buffer, '\0') != buffer + n) {
    return EOF;
  }

  int result = vfscanf(stream, format, arg);

  if(result == EOF) {
    return EOF;
  }

  if(ftell(stream) > BUFSIZ) {
    return EOF;
  }

  return result;
}

int sf_fscanf(FILE *fp, const char *format, ...) { // TODO: Improvements required. Buff overflow, null bytes, invalid inputs
  // Check for NULL stream and format
  if(fp == NULL || format == NULL) {
    fprintf(stderr, "Error: Invalid input.\n");
    return EOF;
  }

  va_list args;
  int ret;
  va_start(args, format);
  ret = sf_vfscanf(fp, format, args); // FIXME: Possible source of problem
  va_end(args);
  return ret;
}

char *sf_strchr(const char *str, int ch) {
  /*
    This implementation checks for null pointers and returns NULL
    if the input string is null. It also checks for buffer overflow by
    iterating through the string until it finds the null terminator.
    If it doesn't find the null terminator, then it returns NULL.
  */
  if(str == NULL) {
    return NULL;
  }

  const char *p = str;

  while(*p != '\0') {
    if(*p == ch) {
      return (char *) p;
    }

    p++;
  }

  return NULL;
}

char *sf_strncat(char *dest, const char *src, size_t n) {
  if(dest == NULL || src == NULL || n == 0) {
    printf("Invalid input\n");
    return dest;
  }

  size_t dest_len = sf_strlen(dest, n);
  size_t src_len = sf_strlen(src, n);

  if(dest_len == n) {
    printf("Destination buffer is already full\n");
    return dest;
  }

  size_t total_len = dest_len + src_len;

  if(total_len >= n) {
    src_len = n - dest_len - 1;
    printf("Source string was truncated to fit the destination buffer\n");
  }

  sf_memmove(dest + dest_len, src, (uint32_t)(src_len + 1));
  dest[dest_len + src_len] = '\0';
  return dest;
}




#define strlen sf_strlen
#define strcpy sf_strcpy
#define strncpy sf_strncpy
#define gets sf_gets
#define scanf sf_scanf
#define sscanf sf_sscanf
#define getchar sf_getchar
#define strcat sf_strcat
#define sprintf sf_sprintf
#define atoi sf_atoi
/*#define vsnprintf sf_vsnprintf*/
#define vsprintf sf_vsprintf
#define vfprintf sf_vfprintf
#define puts sf_puts
#define putc sf_putc
#define putchar sf_putchar
#define getc sf_getc
#define memcpy sf_memcpy
#define fgets sf_fgets
#define memset sf_memset
#define vfscanf sf_vfscanf
#define fscanf sf_fscanf
#define snprintf sf_snprintf
#define strchr sf_strchr
#define strncat sf_strncat
#define fflush sf_fflush_out
#define memmove sf_memmove
#define strlen sf_strlen

