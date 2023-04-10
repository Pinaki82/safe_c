// Last Change: 2023-04-10  Monday: 08:42:23 PM
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "sf_c.h"

#ifndef  MAXBUFF
  #define  MAXBUFF  1E+5f
#endif

void writing_out(char *buf, int buf_size, const char *fmt, ...);

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
  const char *src = "hello";
  size_t n = 5;
  int one_char;
  sf_strcpy(dest, "Hello, world!", sizeof(dest));
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
  return 0;
}

