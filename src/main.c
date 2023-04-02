// Last Change: 2023-04-02  Sunday: 10:35:54 PM
#include <stdio.h>
#include "sf_c.h"
#ifndef  MAXBUFF
  #define  MAXBUFF  1E+5d
#endif
int main() { // main function
  char dest[14]; // increased size of dest array
  char buffer[100];
  const char *src = "hello";
  size_t n = 5;
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
  return 0;
}

