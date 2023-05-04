// Last Change: 2023-05-04  Thursday: 08:35:24 PM
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "sf_c.h"

#ifndef  MAXBUFF
  #define  MAXBUFF  1E+5f
#endif

void vsprintf_test(char const *const format, ...);
void writing_out(char *buf, int buf_size, const char *fmt, ...);

void vsprintf_test(char const *const format, ...) {
  //https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/vsprintf-s-vsprintf-s-l-vswprintf-s-vswprintf-s-l?view=msvc-170
  va_list args;
  int len;
  char *buffer;
  va_start(args, format);
  len = _vscprintf(format, args)   // _vscprintf doesn't count
        + 1; // terminating '\0'
  buffer = (char *) malloc((size_t)len * sizeof(char));

  if(NULL != buffer) {
    sf_vsprintf(buffer, (size_t)len, format, args);
    puts(buffer);
    free(buffer);
  }

  va_end(args);
}

void writing_out(char *buf, int buf_size, const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  sf_vsnprintf(buf, (size_t)buf_size, fmt, args);
  va_end(args);
}

int main() { // main function
  char dest[14]; // increased size of dest array
  int calc_out = 0;
  char buffer[100];
  const char *src = "Hello";
  size_t n = 5;
  int one_char;
  sf_strcpy(dest, "Hello, safety!", sizeof(dest));
  printf("%s\n", dest);
  sf_strncpy(dest, src, n);
  printf("%s\n", dest);

  if(sf_gets(buffer, sizeof(buffer), stdin) != NULL) { // if buffer is not empty
    printf("You entered: %s", buffer);
  }

  printf("%s\n", dest);
  int num = 0;
  printf("Enter a number: ");
  sf_scanf("%d", &num, MAXBUFF);
  printf("You entered: %d\n", num);
  printf("Enter a character: ");
  one_char = sf_getchar();
  printf("The entered character is : %c\n", one_char);
  strcat(dest, src, MAXBUFF);
  printf("Final destination string : |%s|", dest);
  char *string = sf_sprintf("\n%s %d %f", "sf_sprintf", 42, 3.14);

  if(string == NULL) {
    printf("Error: safe_sprintf returned NULL\n");
    return 1;
  }

  printf("%s\n", string);
  free(string);

  if(sf_atoi(dest, &calc_out) == false) { // invalid output = false
    printf("string value = %s, integer value = %d\n", dest, calc_out);
  }

  char fname[20] = "Bell";
  char lname[20] = "Laboratory";
  char lang[5] = "C";
  writing_out(buffer, 100, "%s was created in %s %s\n", lang, fname, lname);
  printf("%s", buffer);
  int option; /* Options */
  printf("Please choose an option:\n");
  printf("1. Clear the screen.\n");
  printf("2. Keep the screen as it is.\n");
  scanf_s("%d", &option);

  if(option == 1) {
    // Code to execute if Option One was chosen
    printf("Clearing the screen.\n");
    sf_cls();
  }

  else if(option == 2) {
    // Code to execute if Option Two was chosen
    printf("Keeping the screen as it is.\n");
  }

  else {
    // Code to execute if an invalid option was chosen
    printf("Invalid option chosen.\n");
  }

  // holds the screen using the custom function
  sf_holdscr();
  sf_puts("Hello, Safety! puts", stdout); // prints "Hello, Safety!\n" to stdout
  sf_puts("Error message!", stderr); // prints "Error message!\n" to stderr
  FILE *pFile;
  int c;
  int n2 = 0;
  char buff2[1024];
  pFile = fopen("../testfile.txt", "r");

  if(pFile == NULL) {
    perror("Error opening file");
  }

  else {
    do {
      c = sf_getc(pFile, buff2, sizeof(buff2));

      if(c == 'r') {
        n2++;
      }
    } while(c != EOF);

    fclose(pFile);
    printf("File contains %d r.\n", n2);
  }

  char str2split[480] = "Wikipedia: Dark matter is a hypothetical form of matter thought to account for approximately 85% of the matter in the universe. Dark matter is called \"dark\" because it does not appear to interact with the electromagnetic field, which means it does not absorb, reflect, or emit electromagnetic radiation and is, therefore, difficult to detect. Most experts think that dark matter is abundant in the universe and has had a strong influence on its structure and evolution.";
  const char splitter[2] = ".";
  char *token;
  /* get the first token */
  token = sf_strtok(str2split, splitter, 500);

  /* walk through other tokens */
  while(token != NULL) {
    printf(" %s!!!\n", token);
    token = sf_strtok(NULL, splitter, 500);
  }

  char str[] = "apple,banana,carrot";
  const char s[2] = ",";
  //char *token2, k = '\0';
  //token2 = &k;
  token = sf_strtok(str, s, sizeof(str));

  while(token != NULL) {
    printf(" %s\n", token);
    token = sf_strtok(NULL, s, sizeof(str));
  }

  vsprintf_test("%d %c %d", 123, '<', 456);
  vsprintf_test("%s", "This is a string");
  int x = 5;
  sf_assert(x > 10);
  printf("x is greater than 10\n");
  printf("This is a test for the fn sf_fflush_out.\n");
  sf_fflush_out(stdout); // Ensure output is written immediately
  fprintf(stderr, "Error message.\n");
  sf_fflush_out(stderr); // Ensure output is written immediately
  return 0;
}

