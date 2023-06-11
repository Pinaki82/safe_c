// Last Change: 2023-06-04  Sunday: 11:24:01 PM
/*
   Licence: Boost Software License, https://www.boost.org/users/license.html
*/

#ifndef  __SF_C_H__
#define  __SF_C_H__

#ifndef errno_t
  typedef int errno_t;
#endif

#if !defined(_WIN32) || !defined(_WIN32_WINNT) || !defined(_WIN32_WINDOWS) || !defined(_WIN64) // https://iq.opengenus.org/detect-operating-system-in-c/
  #include <stddef.h>  // for size_t, sf_strchr(), SIZE_MAX
  #define _POSIX_C_SOURCE 200809L // https://stackoverflow.com/questions/46995050/gcc-warning-implicit-declaration-of-function-strnlen-when-dialect-c99-or-c11
  #define __STDC_WANT_LIB_EXT1__
#else
  #if defined( _WIN32 ) || defined( _WIN64 )
    #include <stddef.h>
  #endif
#endif





//MACRO, global variables, etc..
#define MAXBUFF 100000 // 1E+5f = integer 1x10^+5 = 100000 = 1 M. the max no. chars that will be dealt with.

#ifndef BUFSIZ // needed by sf_getchar()
  #define BUFSIZ 1024
#endif

#define DICT_LEN 256 // needed by create_delim_dict()

#define MAX_BUFFER_LEN 4096 // needed by sf_vsscanf()
#define MAX_FORMAT_LEN 4096 // needed by sf_vsscanf()
#define MAX_LENGTH__VSCPRINTF 4096 // needed by sf_underscore_vscprintf()

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// https://learn.microsoft.com/en-us/cpp/c-runtime-library/file-constants?view=msvc-170
#include <fcntl.h>
#include <stdarg.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
//#include <unistd.h> //TODO: Try compiling without it
#include <stdint.h> // for uint8_t
#include <wchar.h>

#if defined(_WIN32) || defined(_WIN64)
  #include  <windows.h>
#else
  //#include <ncurses.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

int sf_is_valid_input_char(char c);

static inline size_t sf_strnlen(const char *string, size_t length);

/* Initialization of uninitialized variables */
void sf_initialize_int_variable(int *variable);
void sf_initialize_char_variable(char *variable);
void sf_initialize_float_variable(float *variable);
void sf_initialize_double_variable(double *variable);
void sf_initialize_long_variable(long *variable);
void sf_initialize_long_long_variable(long long *variable);
void sf_initialize_unsigned_int_variable(unsigned int *variable);
void sf_initialize_unsigned_char_variable(unsigned char *variable);
void sf_initialize_unsigned_long_variable(unsigned long *variable);
void sf_initialize_unsigned_long_long_variable(unsigned long long *variable);
void sf_initialize_size_t_variable(size_t *variable);
void sf_initialize_short_variable(short *variable);
void sf_initialize_unsigned_short_variable(unsigned short *variable);
void sf_initialize_signed_variable(signed *variable);
void sf_initialize_unsigned_variable(unsigned *variable);
void sf_initialize_boolean_variable(bool *variable);
/* Initialization of uninitialized variables (END)*/

/*usage: sf_memmove(p, s, (uint32_t)(size + 1));*/
void *sf_memmove(void *destn, const void *src, unsigned int n);


size_t sf_strlen(const char *str, size_t max_len); //takes buffer size as an argument

// https://www.tutorialspoint.com/c_standard_library/c_function_strncpy.htm

//note: size=sizeof(dest).
void sf_strcpy(char *dest, const char *src, size_t size);  // Increase size at declaration. The fn takes buffer size as an argument.

void sf_strncpy(char *dest, const char *src, size_t n); //takes buffer size as an argument

//sf_gets(str01, sizeof(str01), stdin); //sizeof(str01) should be 4 to hold cat/dog and 6 to hold apple/mouse
char *sf_gets(char *str, int size, FILE *stream);

int sf_scanf(char *format, void *arg, size_t max_len); //takes buffer size as an argument

int sf_vsscanf(const char *restrict buffer, const char *restrict format, va_list vlist);

int sf_getchar(void);

char *sf_strcat(char *dest, const char *src, size_t dest_size);

int sf_sprintf(char *buffer, const char *format, ...);


bool sf_atoi(const char *str, int *result); // if(sf_atoi(str, &result) == false) // invalid output = false

size_t sf_vsnprintf(char *buffer, size_t size, const char *format, va_list args);

int sf_underscore_vscprintf(const char *format, va_list pargs); // _vscprintf() everywhere

int sf_vsprintf(char *dest, size_t dest_size, const char *format, va_list args); //ensures that the destination buffer is not null and its size is at least 1.

int sf_sscanf(const char *restrict str, const char *restrict format, ...); //checks buffer size taken from an argument and checks for NULL ptrs

// flushes the input buffer
int sf_flush_input_buffer(void);

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
      (void)fprintf(stderr, "Assertion failed: %s\n", #expr); \
      errno = EFAULT; \
      return -1; \
    } \
  } while (0)


// flushes the output buffer
int sf_flush_output_buffer(FILE *stream);

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

char *sf_strdup(const char *s);

char *sf_strndup(const char *s, size_t n);

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

char *sf_strchr(const char *s, int c);

char *sf_strncat(char *dest, const char *src, size_t n);

#ifdef __cplusplus
}
#endif

#endif  /* __SF_C_H__ */

/* Non-global prototypes */


/* A backup function for snprintf() that uses another safe version of vsnprintf(). */
int backup_4_safe_vsnprintf(char *dest, size_t dest_size, const char *format, va_list args);

int *create_delim_dict(const char *delim, size_t max_len); //needed by *sf_strtok()

size_t calculate_required_size(const char *format, va_list args); //needed by sf_vsnprintf()

/* Fn definitions start here */


static inline size_t sf_strnlen(const char *string, size_t length) { //NOTE: Custom implementation.
  //https://e2e.ti.com/support/tools/code-composer-studio-group/ccs/f/code-composer-studio-forum/598070/compiler-cc3220-missing-strnlen
  char *ret = memchr(string, 0, length);
  return (size_t)(ret ? ret - string : (char)length);
}

/*
    Initialization of uninitialized variables.

    These functions will initialize a variable
    if a variable of a function's arguments is uninitialized.
    If any of the arguments are uninitialized, the code will initialize
    them to a default value.
    This helps to prevent errors caused by uninitialized variables.
    USAGE:

    size_t my_fn(char *buffer, size_t size, const char *format, va_list args) {
    // Check if the buffer is uninitialized.
    sf_initialize_char_variable(buffer);

    // ...

    // Do the actual work of the function.

    // ...

    return size;
  }
*/
void sf_initialize_int_variable(int *variable) {
  if(*variable == 0) { // Variable is uninitialized. Initialize it to a default value.
    *variable = 0; //NOBUG: False flag: Either the condition 'variable==NULL' is redundant or there is possible null pointer dereference: variable.
  }
}

void sf_initialize_char_variable(char *variable) {
  if(*variable == '\0') { // Variable is uninitialized. Initialize it to a default value. //NOBUG: False flag: The left operand of '==' is a garbage value.
    *variable = ' ';
  }
}

void sf_initialize_float_variable(float *variable) {
  if(*variable == 0.0) { // Variable is uninitialized. Initialize it to a default value.
    *variable = 0.0; //NOBUG: False flag: Assignment is redundant.
  }
}

void sf_initialize_double_variable(double *variable) {
  if(*variable == 0.0) { // Variable is uninitialized. Initialize it to a default value.
    *variable = 0.0;  //NOBUG: False flag: Assignment is redundant.
  }
}

void sf_initialize_long_variable(long *variable) {
  if(*variable == 0) { // Variable is uninitialized. Initialize it to a default value.
    *variable = 0; //NOBUG: False flag: Assignment is redundant.
  }
}

void sf_initialize_long_long_variable(long long *variable) {
  if(*variable == 0) { // Variable is uninitialized. Initialize it to a default value.
    *variable = 0; //NOBUG: False flag: Assignment is redundant.
  }
}

void sf_initialize_unsigned_int_variable(unsigned int *variable) {
  if(*variable == 0) {
    *variable = 0; //NOBUG: False flag: Assignment is redundant.
  }
}

void sf_initialize_unsigned_char_variable(unsigned char *variable) {
  if(*variable == 0) { // Variable is uninitialized. Initialize it to a default value.
    *variable = 0; //NOBUG: False flag: Assignment is redundant.
  }
}

void sf_initialize_unsigned_long_variable(unsigned long *variable) {
  if(*variable == 0) { // Variable is uninitialized. Initialize it to a default value.
    *variable = 0; //NOBUG: False flag: Assignment is redundant.
  }
}

void sf_initialize_unsigned_long_long_variable(unsigned long long *variable) {
  if(*variable == 0) { // Variable is uninitialized. Initialize it to a default value.
    *variable = 0; //NOBUG: False flag: Assignment is redundant.
  }
}

void sf_initialize_size_t_variable(size_t *variable) {
  if(*variable == 0) { // Variable is uninitialized. Initialize it to a default value.
    *variable = 1; //NOBUG: False flag: Either the condition 'variable==NULL' is redundant or there is possible null pointer dereference: variable.
  }
}

void sf_initialize_short_variable(short *variable) {
  if(*variable == 0) { // Variable is uninitialized. Initialize it to a default value.
    *variable = 0; //NOBUG: False flag: Assignment is redundant.
  }
}

void sf_initialize_unsigned_short_variable(unsigned short *variable) {
  if(*variable == 0) { // Variable is uninitialized. Initialize it to a default value.
    *variable = 0; //NOBUG: False flag: Assignment is redundant.
  }
}

void sf_initialize_signed_variable(signed *variable) {
  if(*variable == 0) { // Variable is uninitialized. Initialize it to a default value.
    *variable = 0; //NOBUG: False flag: Assignment is redundant.
  }
}

void sf_initialize_unsigned_variable(unsigned *variable) {
  if(*variable == 0) { // Variable is uninitialized. Initialize it to a default value.
    *variable = 0; //NOBUG: False flag: Assignment is redundant.
  }
}

void sf_initialize_boolean_variable(bool *variable) {
  if(!*variable) { // Variable is uninitialized. Initialize it to a default value.
    *variable = false;
  }
}
/* Initialization of uninitialized variables (END)*/

/*usage: sf_memmove(p, s, (uint32_t)(size + 1));*/
void *sf_memmove(void *destn, const void *src, unsigned int n) {
  n = n + 1;
  char *pDest = (char *)destn;
  const char *pSrc = (const char *)src;

  if(n < 2) {
    (void)fprintf(stderr, "Invalid memmove() call: !n\n");
    return NULL;
  }

  if(src == NULL) {
    (void)fprintf(stderr, "Invalid memmove() call: src == NULL\n");
    return NULL;
  }

  if(destn == NULL) {
    (void)fprintf(stderr, "Invalid destination buffer\n");
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
        (void)fprintf(stderr, "Destination buffer is not big enough\n");
        return NULL;
      }

      *(pDest + i) = *(pSrc + i);
    }
  }

  return destn;
}

// Based on // https://stackoverflow.com/questions/5935413/is-there-a-safe-version-of-strlen
// Minor changes has been made with the help of ChatGPT and efforts on my part.
/* // https://stackoverflow.com/questions/32599064/is-strlen-unsafe-when-getting-the-last-char-in-a-string-in-c
   // Now, the following will be handled perfectly.
  size_t max_len = 15;
  size_t len;
  char *str = (char *)NULL;
  len = sf_strlen2(str, max_len);  // no segmentation fault -- no crash
*/

//takes buffer size as an argument
size_t sf_strlen(const char *str, size_t max_len) {
  if(str == NULL) {
    // handle null string case
    (void)fprintf(stderr, "%s", "null string!\n");
    return 0;
  }

  else if(max_len == 0) {
    // handle zero length case
    return 0;
  }

  else { // handle non-null string case
    const char *end = (const char *)memchr(str, '\0', max_len); //Explanation: memchr returns a pointer to the first occurrence of a character in a string.

    if(end == NULL) {
      // string is longer than max_len
      return max_len - 1; // length of string minus the null terminator
    }

    else { // string is shorter than max_len
      return (size_t)(end - str); // subtract the null terminator
    }
  }
}

//takes buffer size as an argument
void sf_strcpy(char *dest, const char *src, size_t size) {
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

//takes buffer size as an argument
void sf_strncpy(char *dest, const char *src, size_t n) {
  size_t i;

  for(i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }

  for(; i < n; i++) {
    dest[i] = '\0';
  }
}

//sf_gets(str01, sizeof(str01), stdin); //sizeof(str01) should be 4 to hold cat/dog and 6 to hold apple/mouse
char *sf_gets(char *str, int size, FILE *stream) {
  sf_initialize_char_variable(str);

  // Check for null bytes in the input string and replace them with whitespace chars
  for(size_t i = 0; i < sizeof(size); i++) {
    if((str[i] == '\0') || (!isprint(str[i]))) {
      str[i] = ' ';
    }
  }

  if(size <= 0) {
    (void)fprintf(stderr, "Error: Invalid buffer size. fn sf_gets.\n");
    return NULL;
  }

  if(sf_fgets(str, size, stream) == NULL) { //fgets() returns NULL when the end of the file is reached
    (void)fprintf(stderr, "Error: EOF is reached. fn sf_gets.\n");
    return NULL;
  }

  size_t len = sf_strlen(str, sizeof(str)); //strlen() returns the length of the string in bytes

  if(len > 0 && str[len - 1] == '\n') { //if the last character of the string is a newline
    str[len - 1] = '\0'; //then remove it
  }

  return str; //return the string in the buffer
}

//takes buffer size 'size_t max_len' as an argument
int sf_scanf(char *format, void *arg, size_t max_len) {
  // Read a line of input from stdin
  char *line = (char *)malloc(max_len + 1);

  if(!sf_fgets(line, (int)(max_len + 1), stdin)) {
    // Error reading input
    free(line);
    return EOF;
  }

  // Check if input exceeded max length
  if(sf_strlen(line, MAXBUFF) == max_len && line[max_len - 1] != '\n') {
    // Input exceeded max length
    (void)fprintf(stderr, "Input exceeded maximum length of %zu characters\n", max_len);
    free(line);
    return EOF;
  }

  // Parse the input using sscanf()
  int result = sf_sscanf(line, format, arg);
  free(line);
  return result;
}

//[Wrapper function]
int sf_vsscanf(const char *restrict buffer, const char *restrict format, va_list vlist) {
  int ret;

  if(!buffer || !format) {
    (void)fprintf(stderr, "Null pointer or invalid input passed to sf_vsscanf\n");
    return -1;
  }

  size_t buffer_len = sf_strlen(buffer, MAX_BUFFER_LEN);
  size_t format_len = sf_strlen(format, MAX_FORMAT_LEN);

  // Check for out of bounds
  if(buffer_len >= MAX_BUFFER_LEN || format_len >= MAX_FORMAT_LEN) {
    (void)fprintf(stderr, "Buffer or format is too large in sf_vsscanf\n");
    return -1;
  }

  // Check for empty input
  if((buffer_len == 0) || (format_len == 0)) {
    (void)fprintf(stderr, "Buffer or format is empty in sf_vsscanf\n");
    return -1;
  }

  // Check for null bytes in the input buffer
  for(size_t i = 0; i < buffer_len; i++) {
    if(buffer[i] == '\0') {
      (void)fprintf(stderr, "Null byte passed to sf_vsscanf\n");
      return -1;
    }
  }

  // Check for invalid input characters
  for(size_t i = 0; i < format_len; i++) {
    if(!sf_is_valid_input_char(format[i])) {
      (void)fprintf(stderr, "Invalid input character passed to sf_vsscanf\n");
      return -1;
    }
  }

  ret = vsscanf(buffer, format, vlist); //NOBUG: WARNING: vsscanf() insecure. Won't be fixed. Input checked. Wrapper function.
  return ret;
}

//checks buffer size taken from an argument and checks for NULL ptrs
int sf_sscanf(const char *restrict str, const char *restrict format, ...) {
  if(str == NULL || format == NULL) {
    // Invalid input
    return EOF;
  }

  // Get the length of the input string
  size_t len = sf_strlen(str, MAXBUFF);
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
  int result = sf_vsscanf(str_copy, format, args);
  va_end(args);
  // Free the memory used by the string copy
  free(str_copy);
  return result;
}

int sf_getchar(void) {
  static char buf[BUFSIZ];
  static char *bufp = buf;
  static int n = 0;

  if(n == 0) {
    if(fgets(buf, sizeof(buf), stdin) == NULL) {
      return EOF;
    }

    bufp = buf;
    n = (int)sf_strlen(buf, sizeof(buf));
  }

  if(*bufp != '\0') {
    n--;
    return *bufp++;
  }

  // Check for end-of-file
  if(feof(stdin)) {
    return EOF;
  }

  // Return a default value
  return 0;
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

//takes the size of the destination buffer 'size_t dest_size' as an argument
char *sf_strcat(char *dest, const char *src, size_t dest_size) {
  // Get the length of the destination string
  size_t dest_len = sf_strlen(dest, MAXBUFF);
  // Get the length of the source string
  size_t src_len = sf_strlen(src, MAXBUFF);

  // Check if there is enough space in the destination buffer to append the source string
  if(dest_size - (dest_len + 1) <= src_len) {
    // If there isn't enough space, print an error message to stderr and return NULL
    (void)fprintf(stderr, "safe_strcat: destination buffer is too small\n");
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

int sf_sprintf(char *buffer, const char *format, ...) { //TODO: Initialise variables if not
  if(buffer == NULL || format == NULL) {
    (void)fprintf(stderr, "sf_sprintf: invalid input\n");
    return -1;
  }

  size_t buffer_len = sf_strnlen(buffer, BUFSIZ); //NOTE: Custom implementation used here because of TCC on Windows.

  if(buffer_len == BUFSIZ) {
    (void)fprintf(stderr, "sf_sprintf: buffer is too small\n");
    return -1;
  }

  va_list args;
  va_start(args, format);
  int result = (int)sf_vsnprintf(buffer + buffer_len, BUFSIZ - buffer_len, format, args);
  va_end(args);

  if(((size_t)result < 0) || ((size_t)result >= (BUFSIZ - buffer_len))) { //WARNING: unsignedLessThanZero: Checking if unsigned expression '(unsigned long long)result' is less than zero.
    (void)fprintf(stderr, "sf_sprintf: buffer overflow\n");
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
  int systemRet = system("clear");

  if(systemRet == -1) {
    (void)fprintf(stderr, "sf_cls: system() failed\n");
  }
}
#endif

//checks for invalid input: if(sf_atoi(str, &result) == false) // invalid output = false
bool sf_atoi(const char *str, int *result) { //TODO: Initialise variables if not
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

// Function to calculate the required buffer size for vsnprintf
size_t calculate_required_size(const char *format, va_list args) { //needed by sf_vsnprintf()
  va_list args_copy;
  va_copy(args_copy, args);
  int required_size = vsnprintf(NULL, 0, format, args_copy);
  va_end(args_copy);
  return (required_size >= 0) ? (size_t)(required_size + 1) : 0;  // Add 1 for null terminator
}

//[Wrapper function]
size_t sf_vsnprintf(char *buffer, size_t size, const char *format, va_list args) {//TODO: Check if a null byte is passed. Initialise variables if not. Truncate output before sending to vsnprintf()
  if(buffer == NULL) {
    (void)fprintf(stderr, "Error: buffer is NULL. fn sf_vsnprintf.\n");
    return (size_t)(-1);
  }

  if(size == 0) {
    (void)fprintf(stderr, "Error: size is 0. fn sf_vsnprintf.\n");
    return (size_t)(-1);
  }

  sf_initialize_char_variable(buffer);

  // Check for null bytes in the input buffer and replace them with whitespace chars
  //int found_null = 0;

  for(size_t i = 0; i < sizeof(size); i++) {
    if((buffer[i] == '\0') || (!isprint(buffer[i]))) {
      buffer[i] = ' ';
      //found_null = 1;
    }
  }

  //if(found_null == 1) {
  //(void)fprintf(stderr, "Error: NULL Byte/s were found in sf_vsnprintf. Replaced with whitespace chars.\n");
  //found_null = 0;
  //}
  //
  // Check if the buffer is uninitialized.
  sf_initialize_char_variable(buffer);
  // Check if the size is uninitialized.
  sf_initialize_size_t_variable(&size);
  // Last Change: 2023-06-04  Sunday: 11:25:16 PM
  size_t required_size = calculate_required_size(format, args);

  if(required_size == 0) {
    (void)fprintf(stderr, "Error: Failed to calculate required size. fn sf_vsnprintf.\n");
    return (size_t)(-1);
  }

  // Truncate the output if the buffer size is insufficient
  size_t written = (required_size <= size) ? required_size : size - 1;
  // Call vsnprintf().
  written = (size_t)vsnprintf(buffer, written + 1, format, args);
  // Ensure null termination
  buffer[written] = '\0';
  // Return the number of characters that would have been written if the buffer had sufficient size
  return written;
}

// _vscprintf() everywhere
int sf_underscore_vscprintf(const char *format, va_list pargs) {
  // https://9to5answer.com/replacement-for-ms-_vscprintf-on-macos-linux
  if(format == NULL) {
    (void)fprintf(stderr, "Error: format is NULL. fn sf_underscore_vscprintf. \n");
    return (-1);
  }

  if(sizeof(format) == 0) {
    (void)fprintf(stderr, "Error: format size is 0. fn sf_underscore_vscprintf. \n");
    return (-1);
  }

  // Check if the format is large enough to hold the output.
  if(sizeof(format) < 1) {
    (void)fprintf(stderr, "Error: buffer is too small. fn sf_underscore_vscprintf. \n");
    return (-1);
  }

  char hold[(int)MAX_LENGTH__VSCPRINTF] = "";
  int retval;
  va_list argcopy;
  va_copy(argcopy, pargs);
  retval = (int)sf_vsnprintf(hold, (int)MAX_LENGTH__VSCPRINTF, format, argcopy);
  va_end(argcopy);
  return retval;
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

//ensures that the destination buffer is not null and its size is at least 1.
int sf_vsprintf(char *dest, size_t dest_size, const char *format, va_list args) {
  return (int)sf_vsnprintf(dest, dest_size, format, args);
}

int backup_4_safe_vsnprintf(char *dest, size_t dest_size, const char *format, va_list args) {
  int len = (int)sf_vsnprintf(dest, dest_size, format, args);
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

int sf_flush_input_buffer(void) { // Clear the input buffer.
  /*
    The function first uses a loop with getchar() to consume characters
    until a newline ('\n') or EOF is encountered.
    This step clears the input buffer up to the newline character.

    After that, another loop is used to consume any remaining characters in
    the input buffer until a newline or EOF is reached.
    This ensures that the entire input buffer is cleared, even if there are
    additional characters remaining.

    The function returns the count of characters consumed and cleared
    from the input buffer.
  */
  int c;
  int count = 0;
  //printf("Entering sf_flush_input_buffer()\n");

  // Consume and discard characters until a newline or EOF is encountered
  while((c = sf_getchar()) != '\n' && c != EOF) {
    count++;
    //printf("Consumed character: %c (ASCII: %d)\n", c, c);
  }

  //printf("Exited first loop\n");
  // Clear any remaining characters in the input buffer
  int remaining;

  while((remaining = sf_getchar()) != '\n' && remaining != EOF) {
    count++;
    //printf("Discarded character: %c (ASCII: %d)\n", remaining, remaining);
  }

  //printf("Exited second loop\n");
  //printf("Exiting sf_flush_input_buffer()\n");
  return count;
}

// function: holds the screen before the text disappears
void sf_holdscr(void) {
#ifdef _WIN32
  system("pause >nul"); // pause >nul redirects the output of the pause command to nul to suppress the "Press any key to continue . . ." message.
#else
  /* prints a message to the console, flushes the buffer, and then reads a single character from the user input without echoing it to the terminal using the read command. Finally, it prints a newline character to ensure the cursor is on a new line before continuing. */
  printf("Press any key to continue...");
  (void)fflush(stdout);
  (void)system("read ans"); // https://unix.stackexchange.com/questions/293940/how-can-i-make-press-any-key-to-continue
  printf("\n");
#endif
}

int sf_flush_output_buffer(FILE *stream) {
  /* checks whether the stream is stdin. if so, returns error. */
  if(stream != stdin) {
    (void)fflush(stream);
    return (0);
  }

  else if(stream == stdin) {
    (void)fprintf(stderr, "Error: passed \'stdin\' to the fn sf_fflush_out.\n");
    return (-1);
  }

  else {
    (void)fprintf(stderr, "Error: the fn sf_fflush_out encountered a strange error.\n");
    return (-1);
  }
}

/* From: sf_c.h */
//[Wrapper function]
int sf_vfprintf(FILE *stream, const char *format, va_list ap) {
  // Check for a null file pointer
  if(!stream) {
    return -1;
  }

  // Call vfprintf() with the given arguments
  return vfprintf(stream, format, ap); //NOBUG: False flag: 'format' is not a string-literal
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

  (void)fprintf(stream, "%s\n", sanitized_str);
  free(sanitized_str);
}

int sf_putc(int c, FILE *stream) {
  if(!isprint(c)) {
    (void)fprintf(stderr, "Error: Non-printable character detected in input.\n");
    return EOF;
  }

  return fputc(c, stream);
}

int sf_putchar(int c) {
  //[Wrapper function]
  if(!isprint(c) || c == '\n' || c == '\r' || c == '\t') {
    return EOF;  // reject non-printable characters and control characters
  }

  return putchar(c);  // safe to write to stdout
}

// _is_valid_input_char() in C, everywhere
int sf_is_valid_input_char(char c) {
  return isprint((unsigned char) c);
}

//[Wrapper function]
int sf_getc(FILE *stream, char *buffer, size_t buflen) {
  if(!buffer || buflen == 0) {
    return EOF;
  }

  int c = getc(stream);

  if(c == EOF) {
    buffer[0] = '\0';
    return EOF;
  }

  if(sf_is_valid_input_char((char)c)) {
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

// strdup() everywhere
char *sf_strdup(const char *s) {
  size_t size = sf_strlen(s, MAXBUFF) + 1;
  char *p;
  p = (char *)malloc((size_t)(size) * sizeof(char));

  if(p == NULL) {
    (void)fprintf(stderr, "\ndynamic memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  if(p != NULL) { //NOBUG: WARNING: condition p!=NULL always true. False flag: The condition is there for making the function failsafe.
    sf_memmove(p, s, (uint32_t)(size + 1));
  }

  else {
    free(p);
    p = NULL;
  }

  return p;
}

//strndup() everywhere
char *sf_strndup(const char *s, size_t n) {
  char *p;
  size_t n1;

  for(n1 = 0; n1 < n && s[n1] != '\0'; n1++) {
    continue; //WARNING: continue is redundant since it is the last statement in a loop
  }

  p = (char *)malloc((size_t)(n + 1) * sizeof(char));

  if(p == NULL) {
    (void)fprintf(stderr, "\ndynamic memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  if(p != NULL) { //NOBUG: WARNING: condition p!=NULL always true. False flag: The condition is there for making the function failsafe.
    sf_memmove(p, s, (uint32_t)(n1 + 1));
    p[n1] = '\0';
  }

  else {
    free(p);
    p = NULL;
  }

  return p;
}

//[Wrapper function]
char *sf_fgets(char *s, int size, FILE *stream) {
  if(size <= 0) {
    (void)fprintf(stderr, "Error: Invalid buffer size.\n");
    return NULL;
  }

  char *ret = fgets(s, size, stream); //Inside the wrapper (sf_fgets is fgets)

  if(ret == NULL || sf_strlen(ret, sizeof(ret)) == 0) {
    if(feof(stream)) {
      return NULL;
    }

    else {
      // Some other error occurred
      (void)fprintf(stderr, "Error reading from input stream.\n");
      return NULL;
    }
  }

  // Remove the newline character at the end, if present
  size_t len = sf_strlen(s, MAXBUFF);

  if(len > 0 && s[len - 1] == '\n') {
    s[len - 1] = '\0';
  }

  // Sanitize the string by replacing non-printable characters with spaces
  for(size_t i = 0; i < len; i++) {
    if(!isprint(s[i])) {
      s[i] = ' ';
    }
  }

  // Check for end-of-file
  if(feof(stream)) {
    return NULL;
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

//needed by *sf_strtok()
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
    sf_strncpy(last_token, str, max_len);
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

//[Wrapper function]
int sf_vfscanf(FILE *stream, const char *format, va_list arg) {
  /*
    - The function first formats the input string using vsnprintf() and stores it in a buffer.
    - It then checks for buffer overflow by comparing the length of the formatted string with the size of the buffer.
    - It also checks for null bytes by searching for the first null byte in the buffer.
    - Finally, it calls vfscanf() to read input from the stream and checks if the file position indicator is within bounds.
  */
  char buffer[BUFSIZ];
  va_list arg_copy;
  va_copy(arg_copy, arg);
  int n = (int)sf_vsnprintf(buffer, BUFSIZ - 1, format, arg_copy);
  va_end(arg_copy);

  if(n < 0 || n >= BUFSIZ) {
    (void)fprintf(stderr, "Error: buffer overflow in sf_vfscanf.\n");
    return EOF;
  }

  if(sf_strchr(buffer, '\0') != buffer + n) {
    (void)fprintf(stderr, "Error: Null bytes in sf_vfscanf.\n");
    return EOF;
  }

  va_copy(arg_copy, arg);
  int result = vfscanf(stream, format, arg_copy); //NOBUG: Won't be fixed. Input checked. In a wrapper function.
  //NOBUG: False flag: 'format' is not a string-literal
  va_end(arg_copy);

  if(result == EOF) {
    (void)fprintf(stderr, "Error: Invalid input in sf_vfscanf.\n");
    return EOF;
  }

  if(ftell(stream) > BUFSIZ) {
    (void)fprintf(stderr, "Error: File position indicator out of bounds in sf_vfscanf.\n");
    return EOF;
  }

  return result;
}

int sf_fscanf(FILE *fp, const char *format, ...) { // TODO: Improvements required. Buff overflow, null bytes, invalid inputs
  // Check for NULL stream and format
  if(fp == NULL || format == NULL) {
    (void)fprintf(stderr, "Error: Invalid input passed to sf_fscanf.\n");
    return EOF;
  }

  va_list args;
  int ret;
  va_start(args, format);
  ret = sf_vfscanf(fp, format, args);
  va_end(args);
  return ret;
}

char *sf_strchr(const char *s, int c) {
  /* This implementation returns a pointer to the first occurrence
     of the character c in the string s.
     If the character is not found, it returns NULL. */
  if(s == NULL) {
    (void)fprintf(stderr, "Error: Invalid input passed to my_strchr.\n");
    return NULL;
  }

  while(*s != '\0') {
    if(*s == (char)c) {
      return (char *)s;
    }

    s++;
  }

  if(c == '\0') {
    return (char *)s;
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
    /*(void)printf("Source string was truncated to fit the destination buffer\n");*/
  }

  sf_memmove(dest + dest_len, src, (uint32_t)(src_len + 1));
  dest[dest_len + src_len] = '\0';
  return dest;
}

