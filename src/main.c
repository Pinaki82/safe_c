// Last Change: 2023-05-07  Sunday: 01:06:36 AM
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "sf_c.h"

#ifndef  MAXBUFF
  #define  MAXBUFF  1E+5f
#endif

#define MAXCHARSIZE 100

void vsprintf_test(char const *const format, ...);
void writing_out(char *buf, int buf_size, const char *fmt, ...);
void writeFormattedOutput(FILE *stream, const char *format, ...);

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

void writeFormattedOutput(FILE *stream, const char *format, ...) {
  va_list args;
  va_start(args, format);
  sf_vfprintf(stream, format, args);
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
  FILE *fp;
  int karctr; // ASCII character
  fp = fopen("../testfile2.txt", "w+"); // open file for writing

  for(karctr = 33 ; karctr <= 100; karctr++) { // loop through the printable ASCII characters
    sf_putc(karctr, fp); // write the character to the file
  }

  fclose(fp); // close the file
  fp = fopen("../testfile2.txt", "a");
  fprintf(fp, "\n");
  fclose(fp);
  printf("See the contents of the file \"testfile2.txt\"\n");
  char krctr_chtype;

  for(krctr_chtype = '1'; krctr_chtype <= '9'; krctr_chtype++) { // prints 1 to 9
    sf_putchar(krctr_chtype);
  }

  printf("\n");
  const char srcstr[50] = "Terminal";
  char deststr[50];
  sf_strcpy(deststr, "Emulator!", (size_t)sizeof(deststr));
  sf_puts("deststr: before memcpy: \n", stdout);
  sf_puts(deststr, stdout);
  /* Copy contents of the source to the destination */
  sf_memcpy(deststr, srcstr, (sf_strlen(srcstr, (size_t)(sizeof(deststr)))));
  sf_puts("deststr: after sf_memcpy: \n", stdout);
  sf_puts(deststr, stdout);
  printf("\n");
  char *str_4_strdup_src = "strdupTest";
  char *str_4_strdup_target = strdup(str_4_strdup_src);
  printf("%s\n", str_4_strdup_target);
  char *str_4_strndup_src = "strNdupTest";
  char *str_4_strndup_target = strndup(str_4_strndup_src, 7);
  printf("%s\n", str_4_strndup_target);
  FILE *file3;
  char str_4_fscanf_1[10], str_4_fscanf_2[10], str_4_fscanf_3[10], str_4_fscanf_4[50];
  file3 = fopen("../testfile3.txt", "w+");
  fputs("We are testing fscanfTest\n", file3);
  fclose(file3);
  file3 = fopen("../testfile3.txt", "r");
  rewind(file3);
  sf_fscanf(file3, "%s %s %s %s", str_4_fscanf_1, str_4_fscanf_2, str_4_fscanf_3, str_4_fscanf_4);
  printf("Read String1 |%s|\n", str_4_fscanf_1);
  printf("Read String2 |%s|\n", str_4_fscanf_2);
  printf("Read String3 |%s|\n", str_4_fscanf_3);
  printf("Read String4 |%s|\n", str_4_fscanf_4);
  fclose(file3);
  char buffer_4_snprintf[50];
  char *s2 = "\"HereIsMyName: Appu.\"";
  printf("Writing %s onto buffer with capacity 15\n", s2);
  int retval01 = sf_snprintf(buffer_4_snprintf, 15, "%s\n", s2);
  printf("String written on buffer = %s\n", buffer_4_snprintf);
  printf("Value returned by sf_snprintf() method = %d\n", retval01);
  char dtm[MAXCHARSIZE];
  char weekday[20], month[20];
  int day, year;
  // Set the date/time string
  sf_strcpy(dtm, "Saturday March 25 1989", MAXCHARSIZE);

  // Parse the date/time string using sf_sscanf()
  if(sf_sscanf(dtm, "%s %s %d %d", weekday, month, &day, &year, MAXCHARSIZE) != 4) {
    printf("Error: failed to parse date/time string.\n");
    return 1;
  }

  // Print the parsed date/time values
  printf("%s %d, %d = %s\n", month, day, year, weekday);
  char myname[100] = "Pinaki ", mysurname[] = "Gupta", completename[150];
  int count = 0;

  do {
    *(completename + count) = '\0';
    count++;
  } while(count < 150);

  sf_strcat(completename, myname, 150);
  sf_strcat(completename, mysurname, 150);
  printf("%s\n", myname);
  printf("%s\n", mysurname);
  printf("%s\n", completename);
  FILE *pFile2;
  pFile2 = fopen("../testfile4.txt", "w");
  writeFormattedOutput(pFile2, "Call with %d variable argument.\n", 1);
  writeFormattedOutput(pFile2, "Call with %d variable %s.\n", 2, "arguments");
  fclose(pFile2);
  printf("see the output file textfile4.txt\n");
  const char strtest001[] = "Wikipedia is a multilingual, free, online encyclopedia written and maintained by a community of volunteers.";
  const char ch = ',';
  char *ret;
  ret = sf_strchr(strtest001, ch);
  printf("String after |%c| is - |%s|\n", ch, ret);
  sf_holdscr();
  int x = 5;
  sf_assert(x > 10);
  printf("x is greater than 10\n");
  printf("This is a test for the fn sf_fflush_out.\n");
  sf_fflush_out(stdout); // Ensure output is written immediately
  fprintf(stderr, "Error message.\n");
  sf_fflush_out(stderr); // Ensure output is written immediately
  return 0;
}

