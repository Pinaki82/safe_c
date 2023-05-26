// Last Change: 2023-05-26  Friday: 10:35:44 PM
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h> // Include the necessary header for vswprintf
#include "sf_c.h"

#ifndef  MAXBUFF
  #define  MAXBUFF  1E+5f
#endif

#define MAXCHARSIZE 100
#define MAX_LENGTH_STRNCAT 20

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
#define vsnprintf sf_vsnprintf
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
#define memmove sf_memmove
#define strdup sf_strdup
#define strndup sf_strndup
#define is_valid_input_char sf_is_valid_input_char

#define VERSION "1" /* defines a constant string called "VERSION" with the value 1 */
#define NO_OF_ARGS 2 /* the exact no. of command-line arguments the program takes */

void vsprintf_test(char const *const format, ...);
void writing_out(char *buf, int buf_size, const char *fmt, ...);
void writeFormattedOutput(FILE *stream, const char *format, ...);

void vsprintf_test(char const *const format, ...) {
  //https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/vsprintf-s-vsprintf-s-l-vswprintf-s-vswprintf-s-l?view=msvc-170
  va_list args;
  int len;
  char *buffer;
  va_start(args, format);
  len = sf_underscore_vscprintf(format, args)   // _vscprintf doesn't count
        + 1; // terminating '\0'
  buffer = (char *) malloc((size_t)len + 1 * sizeof(char));

  if(NULL != buffer) {
    sf_vsprintf(buffer, (size_t)len, format, args);
    sf_puts(buffer, stdout);
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

int main(int argc, char *argv[]) { // main function
  printf("Hey! \"%s\" here!\n", argv[0]); /* Displays the program's name */

  if(argc == 2 && strcmp(argv[1], "--version") == 0) { /* checks if the program was called with the argument "--version". If it was, it prints out the value of the "VERSION" constant and returns 0. Otherwise, it slides down to the next `else if()` block. */
    printf("%s\n", VERSION);
    return 0;
  }

  else if(argc == 2 && strcmp(argv[1], "-r") == 0) { /* checks if the program was called with only ONE argument and the argument was not "-r". */
    printf("supplied argument: -r. The program will run.\n");
  }

  else if((argc == 2 && strcmp(argv[1], "--version") != 0) || (argc == 2 && strcmp(argv[1], "-r") != 0)) { /* checks if the program was called with only ONE argument and the argument was not "--version". In that case, it displays an error message and exits with a return value of 1. */
    printf("Unknown argument! The program will exit!!\n");
    exit(1);
  }

  if(argc != NO_OF_ARGS) {  /* Checks if the program was called with the exact number of arguments. If it wasn't, it prints out an error message and returns 1. */
    printf("Please provide %d arguments\n", (NO_OF_ARGS - 1));
    return 1;
  }

  /* After performing all checks, your code starts here */
  printf("First argument: %s\n", argv[1]); /* prints out the first argument passed to the program */
  printf("                                            test: sf_strcpy\n");
  char dest[14]; // increased size of dest array
  int calc_out = 50;
  char buffer[300];
  const char *src = "Hello";
  size_t n = 5;
  int one_char;
  sf_strcpy(dest, "Hello, safety!", sizeof(dest));
  printf("%s\n", dest);
  printf("                                            test: sf_strncpy\n");
  sf_strncpy(dest, src, n);
  printf("%s\n", dest);
  printf("                                            test: sf_gets\n");
  printf("Type something and hit Enter\n");

  if(sf_gets(buffer, sizeof(buffer), stdin) != NULL) { // if buffer is not empty
    printf("You entered: %s", buffer);
  }

  printf("%s\n", dest);
  printf("                                            test: sf_scanf\n");
  int num = 0;
  printf("Enter a number: ");
  sf_scanf("%d", &num, MAXBUFF);
  printf("You entered: %d\n", num);
  // Clear the input buffer.
  sf_flush_input_buffer();
  printf("                                            test: sf_getchar\n");
  // Clear the input buffer.
  sf_flush_input_buffer();
  printf("Enter a character: ");
  one_char = sf_getchar();
  printf("The entered character is : %c\n", one_char);
  // Clear the input buffer.
  sf_flush_input_buffer();
  printf("                                            test: sf_strcat\n");
  sf_strcat(dest, src, MAXBUFF);
  printf("Final destination string : |%s|", dest);
  printf("\n");
  // Clear the input buffer.
  sf_flush_input_buffer();

  for(int i = 0; i < (int)sizeof(buffer); i++) {
    buffer[i] = '\0'; //clean up the stored value
  }

  printf("                                            test: sf_sprintf\n");
  int aa = 10, bb = 20, cc; //https://www.geeksforgeeks.org/sprintf-in-c/
  cc = aa + bb;
  printf("\n");
  sf_sprintf(buffer, "Sum of %d and %d is %d\n", aa, bb, cc);
  // The string "sum of 10 and 20 is 30" is stored
  // into the buffer instead of printing to stdout
  printf("%s\n", buffer);
  printf("                                            test: sf_strndup\n");
  printf("                                            test: sf_strlen\n");
  char *str_hi = "Hi, there!";
  char *new_str = sf_strndup(str_hi, sf_strlen(str_hi, BUFSIZ) - 1);
  printf("The new string is: \"%s\" from \"Hi, there!\"\nsf_strlen size %llu\n", new_str, sf_strlen(str_hi, BUFSIZ));
  printf("                                            test: sf_gets\n");
  printf("                                            test: sf_scanf\n");
  //https://overiq.com/c-programming-101/the-sprintf-function-in-c/
  int factorial(int);
  int sal;
  char name[30] = "", designation[30] = "", info[60] = "";
  printf("Enter your name: ");
  sf_gets(name, sizeof(name), stdin);
  printf("Enter your designation: ");
  sf_gets(designation, sizeof(designation), stdin);
  printf("Enter your salary: ");
  sf_scanf("%d", &sal, 10);
  printf("\n");
  printf("                                            test: sf_sprintf\n");
  sf_sprintf(info, "Welcome %s !\nName: %s \nDesignation: %s\nSalary: %d",
             name, name, designation, sal);
  printf("\n%s\n", info);
  printf("                                            test: sf_atoi\n");

  if(sf_atoi(dest, &calc_out) == false) { // invalid output = false
    printf("string value = %s, integer value = %d\n", dest, calc_out);
  }

  char fname[20] = "Bell";
  char lname[20] = "Laboratory";
  char lang[5] = "C";
  writing_out(buffer, 100, "%s was created in %s %s\n", lang, fname, lname);
  printf("%s", buffer);
  int option = 0; /* Options */
  printf("Please choose an option:\n");
  printf("1. Clear the screen.\n");
  printf("2. Keep the screen as it is.\n");
  printf("                                            test: sf_scanf\n");
  sf_scanf("%d", &option, MAXBUFF);
  //scanf_s("%d", &option);

  if(option == 1) {
    printf("                                            test: sf_cls\n");
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

  printf("                                            test: sf_holdscr\n");
  // holds the screen using the custom function
  sf_holdscr();
  printf("                                            test: sf_puts\n");
  sf_puts("Hello, Safety! puts", stdout); // prints "Hello, Safety!\n" to stdout
  printf("                                            test: sf_puts\n");
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
    printf("                                            test: sf_getc\n");

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
  printf("                                            test: sf_strtok\n");
  /* get the first token */
  token = sf_strtok(str2split, splitter, 500);
  printf("                                            test: sf_strtok\n");

  /* walk through other tokens */
  while(token != NULL) {
    printf(" %s!!!\n", token);
    token = sf_strtok(NULL, splitter, 500);
  }

  char str[] = "apple,banana,carrot";
  const char s[2] = ",";
  //char *token2, k = '\0';
  //token2 = &k;
  printf("                                            test: sf_strtok\n");
  token = sf_strtok(str, s, sizeof(str));
  printf("                                            test: sf_strtok\n");

  while(token != NULL) {
    printf(" %s\n", token);
    token = sf_strtok(NULL, s, sizeof(str));
  }

  printf("                                            test: vsprintf_test\n");
  vsprintf_test("%d %c %d", 123, '<', 456);
  printf("                                            test: vsprintf_test\n");
  vsprintf_test("%s", "This is a string");
  FILE *fp;
  int karctr; // ASCII character
  fp = fopen("../testfile2.txt", "w+"); // open file for writing
  printf("                                            test: sf_putc\n");

  for(karctr = 33 ; karctr <= 100; karctr++) { // loop through the printable ASCII characters
    sf_putc(karctr, fp); // write the character to the file
  }

  fclose(fp); // close the file
  fp = fopen("../testfile2.txt", "a");
  fprintf(fp, "\n");
  fclose(fp);
  printf("See the contents of the file \"testfile2.txt\"\n");
  char krctr_chtype;
  printf("                                            test: sf_putchar\n");

  for(krctr_chtype = '1'; krctr_chtype <= '9'; krctr_chtype++) { // prints 1 to 9
    sf_putchar(krctr_chtype);
  }

  printf("\n");
  const char srcstr[50] = "Terminal";
  char deststr[50];
  printf("                                            test: sf_strcpy\n");
  sf_strcpy(deststr, "Emulator!", (size_t)sizeof(deststr));
  printf("                                            test: sf_puts\n");
  sf_puts("deststr: before memcpy: \n", stdout);
  printf("                                            test: sf_puts\n");
  sf_puts(deststr, stdout);
  printf("                                            test: sf_memcpy\n");
  /* Copy contents of the source to the destination */
  sf_memcpy(deststr, srcstr, (sf_strlen(srcstr, (size_t)(sizeof(deststr)))));
  printf("                                            test: sf_puts\n");
  sf_puts("deststr: after sf_memcpy: \n", stdout);
  printf("                                            test: sf_puts\n");
  sf_puts(deststr, stdout);
  printf("\n");
  char *str_4_strdup_src = "strdupTest";
  printf("                                            test: sf_strdup\n");
  char *str_4_strdup_target = sf_strdup(str_4_strdup_src);
  printf("%s\n", str_4_strdup_target);
  char *str_4_strndup_src = "strNdupTest";
  printf("                                            test: sf_strndup\n");
  char *str_4_strndup_target = sf_strndup(str_4_strndup_src, 7);
  printf("%s\n", str_4_strndup_target);
  FILE *file3;
  char str_4_fscanf_1[10], str_4_fscanf_2[10], str_4_fscanf_3[10], str_4_fscanf_4[50];
  file3 = fopen("../testfile3.txt", "w+");
  printf("                                            test: fputs\n");
  fputs("We are testing fscanfTest\n", file3);
  fclose(file3);
  file3 = fopen("../testfile3.txt", "r");
  rewind(file3);
  printf("                                            test: sf_fscanf\n");
  sf_fscanf(file3, "%s %s %s %s", str_4_fscanf_1, str_4_fscanf_2, str_4_fscanf_3, str_4_fscanf_4);
  printf("Read String1 |%s|\n", str_4_fscanf_1);
  printf("Read String2 |%s|\n", str_4_fscanf_2);
  printf("Read String3 |%s|\n", str_4_fscanf_3);
  printf("Read String4 |%s|\n", str_4_fscanf_4);
  fclose(file3);
  char buffer_4_snprintf[50];
  char *s2 = "\"HereIsMyName: Appu.\"";
  printf("Writing %s onto buffer with capacity 15\n", s2);
  printf("                                            test: sf_snprintf\n");
  int retval01 = sf_snprintf(buffer_4_snprintf, 15, "%s\n", s2);
  printf("String written on buffer = %s\n", buffer_4_snprintf);
  printf("Value returned by sf_snprintf() method = %d\n", retval01);
  char dtm[MAXCHARSIZE];
  char weekday[20], month[20];
  int day, year;
  // Set the date/time string
  printf("                                            test: sf_strcpy\n");
  sf_strcpy(dtm, "Saturday March 25 1989", MAXCHARSIZE);
  printf("                                            test: sf_sscanf\n");

  // Parse the date/time string using sf_sscanf()
  if(sf_sscanf(dtm, "%s %s %d %d", weekday, month, &day, &year, MAXCHARSIZE) != 4) {
    printf("Error: failed to parse date/time string.\n");
    return 1;
  }

  // Print the parsed date/time values
  printf("%s %d, %d = %s\n", month, day, year, weekday);
  char myname[100] = "Pinaki ", mysurname[] = "Gupta", completename[150] = "" /* initialize dest to an empty string */;
  printf("                                            test: sf_strcat\n");
  sf_strcat(completename, myname, 150);
  printf("                                            test: sf_strcat\n");
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
  printf("                                            test: sf_strchr\n");
  ret = sf_strchr(strtest001, ch);
  printf("String after |%c| is - |%s|\n", ch, ret);
  char destStrncat[MAX_LENGTH_STRNCAT] = "Hello";
  char srcStrncat[10] = "ChatGPT";
  printf("                                            test: sf_strncat\n");
  sf_strncat(destStrncat, srcStrncat, MAX_LENGTH_STRNCAT);
  printf("%s\n", destStrncat);
  printf("                                            test: sf_holdscr\n");
  sf_holdscr();
  printf("                                            test: sf_assert\n");
  int x = 5;
  sf_assert(x > 10);
  printf("x is greater than 10\n");
  printf("This is a test for the fn sf_flush_output_buffer.\n");
  printf("                                            test: sf_flush_output_buffer\n");
  sf_flush_output_buffer(stdout); // Ensure output is written immediately
  fprintf(stderr, "Error message.\n");
  printf("                                            test: sf_flush_output_buffer\n");
  sf_flush_output_buffer(stderr); // Ensure output is written immediately
  return 0;
}

