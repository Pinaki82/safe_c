// Last Change: 2023-04-03  Monday: 12:07:14 AM
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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>  // for size_t
#include <string.h>
// https://learn.microsoft.com/en-us/cpp/c-runtime-library/file-constants?view=msvc-170
#include <fcntl.h>


#ifdef __cplusplus
extern "C" {
#endif

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

// an alternative function to sscanf() that checks buffer size as an argument
int sf_sscanf(const char *str, const char *format, void *arg, size_t max_len);

// an alternative function to getchar(() that handles input more appropriately
int sf_getchar(void);

// an alternative function to strcat() that handles input more appropriately
char *sf_strcat(char *dest, const char *src, size_t dest_size);


#ifdef __cplusplus
}
#endif

#endif  /* __SF_C_H__ */

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
void sf_strcpy(char *dest, const char *src, size_t size) { //size=sizeof(dest). Increase size at declaration.
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
  int result = sscanf(line, format, arg);
  free(line);
  return result;
}

// an alternative function to sscanf() that checks buffer size as an argument
int sf_sscanf(const char *str, const char *format, void *arg, size_t max_len) {
  // Allocate memory for a copy of the string
  char *str_copy = (char *)malloc(max_len + 1);

  if(!str_copy) {
    // Failed to allocate memory
    return EOF;
  }

  // Copy the input string
  strncpy(str_copy, str, max_len);
  str_copy[max_len] = '\0';
  // Parse the input using sscanf()
  int result = sscanf(str_copy, format, arg);
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

  while(*dest_end != '\0' && dest_end - dest < dest_size) {
    // Find the end of the destination string
    ++dest_end;
  }

  // Copy the source string to the end of the destination string
  while(*src != '\0' && dest_end - dest < dest_size - 1) {
    *dest_end++ = *src++;
  }

  // Add a null terminator to the end of the string
  if(dest_end - dest < dest_size) {
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

#define strlen sf_strlen
#define strcpy sf_strcpy
#define strncpy sf_strncpy
#define gets sf_gets
#define scanf sf_scanf
#define sscanf sf_sscanf
#define getchar sf_getchar
#define strcat sf_strcat


