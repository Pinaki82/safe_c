# safe_c

Set of Custom **C Functions** that are **Safe Alternatives**.

# What is it?

_Long story short: It's a C library with a set of functions._

Compare the two following programs.

1. Program One:

```c
// gcc -Wall -Wextra -pedantic -O2 -g test.c -o test
// chmod +x test
// ./test

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 4 //to hold cat/dog. 6 to hold apple/mouse

int main(void) {
  char str01[MAXLEN] = "";
  printf("Enter a string: ");
  gets(str01);
  printf("string is: %s\n", str01);
  return 0;
}
```

```
./test
Enter a string: catss
string is: catss
*** stack smashing detected ***: terminated
Aborted (core dumped)
```

2. Program Two:

```c
// gcc -Wall -Wextra -pedantic -O2 -g test.c -o test
// chmod +x test
// ./test

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sf_c.h"

#define MAXLEN 4 //to hold cat/dog. 6 to hold apple/mouse

int main(void) {
  char str01[MAXLEN] = "";
  printf("Enter a string: ");
  sf_gets(str01, sizeof(str01), stdin); // Look here
  printf("string is: %s\n", str01);
  return 0;
}
```

```
./test
Enter a string: catss
string is: cat
```

Or,

```c
// Last Change: 2023-05-19  Friday: 11:56:18 PM
// gcc -Wall -Wextra -pedantic -O2 -g test.c -o test
// chmod +x test
// ./test

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sf_c.h"

#define MAXLEN 5 //to hold cat/dog. 6 to hold apple/mouse

int main(void) {
  char *str01 = (char *)malloc((size_t)MAXLEN * sizeof(char));

  if(str01 == NULL) {
    fprintf(stderr, "\ndynamic memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  printf("Enter a string: ");
  sf_gets(str01, MAXLEN, stdin);
  printf("size is: %d, string is: %s\n", MAXLEN, str01);
  free(str01);
  str01 = NULL;
  return 0;
}
```

Or,

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sf_c.h"

#define MAXLEN 4

int main(void) {
  char str01[MAXLEN] = "";
  printf("Enter a string: ");
  sf_gets(str01, MAXLEN, stdin); //perfectly fine
  printf("string is: %s\n", str01);
  return 0;
}
```

```
./test
Enter a string: catos
size is: 5, string is: cato
```

The version of the function `gets()` with the `sf_` prefix (i.e., `sf_gets()`) seems to be more secure. Not?

## What's not possible!

However, one can easily crash the program by doing something completely thoughtless as:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/sf_c.h"

#define MAXLEN 4 //to hold cat/dog. 6 to hold apple/mouse

int main(void) {
  char str01[MAXLEN] = "";
  printf("Enter a string: ");
  sf_gets(str01, 6, stdin); //str01 can hold 4 ASCII chars at max, not 6
  printf("string is: %s\n", str01);
  return 0;
}
```

**Reason:** No matter how hard one tries to calculate the size of a passed array/string(a `char` array) in the 'callee' function using `sizeof(str)` in the 'callee', he won't be able to calculate the correct value of `sizeof(str)` from the 'callee' function. When you pass an array to a function, the function only receives a pointer to the first element of the array. The size of the array is not passed along with the pointer. Therefore, the 'callee' function cannot know the size of the array.

To get the size of the array, you need to pass it as an argument to the function. For example:

```c
void callee(char *str, int size) {
  // Do something with str
}

int main() {
  char str01[MAX] = "";
  callee(str01, MAX);
  return 0;
}
```

Basically, there's no way of determining the size of the passed string right in the 'callee' function! The only way to get the size of the string is to pass it as an argument to the function. Even something like the code below will not work.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 4

void callee(char *str, int size);

void callee(char *str, int size) {
  int len = strlen(str);
  // Do something with str
  printf("len = %ld, size received = %d\n", len, size);
}

int main() {
  char str01[MAX] = "";
  callee(str01, MAX);
  return 0;
}
```

```
len = 0, size received = 4
```

The 'callee' function can only access the data that is passed to it. It cannot access any other data that is stored in the caller function. Passing the entire array will only tell the 'callee' function that the function only received a pointer to the first element of the array, not the size of the array. The 'callee' has no way to determine the size of the passed array since the size is not passed along with the pointer.

If it was possible to manage that size calculation part inside the 'callee' (here, the functions with the `sf_` prefix), I would do that.

So, there's no cure for inattentive, sleepy-mood writing. A very few basic rules have to be taken care of. Those one or two extra steps won't be labour-intensive in any way, either. Read instructions for the `sf_` prefixed functions. They'll be fine.

# How can I build the library?

The aim of the [safe_c library](https://github.com/Pinaki82/safe_c.git) are:

1. To replace some C standard library functions (that are not very safe) with alternative custom functions. #Re-implementation.

2. Portability: To maintain portability across compilers and platforms as much as possible without the need to build the library. The library will contain one header file that can be dropped inside your project's include directory and be used immediately, even at the cost of readability in terms of code navigation in the header.

3. Re-implement functions as much as possible taking as little as possible from the C standard library.

4. Freedom: The library is released under the [Boost Software License - Version 1.0 - August 17th, 2003](https://www.boost.org/users/license.html); since it is a tool, it is a library, and it has to be free to use for any purpose without unnecessary restrictions.

### Disclaimer:

I took advantage of AI software solutions from many providers, this includes [ChatGPT](https://chat.openai.com/chat), [Bard](https://bard.google.com/), [Codeium](https://codeium.com/), [Open Assistant](https://open-assistant.io/dashboard), [Playground - OpenAI API](https://platform.openai.com/playground), [lmsys.org](https://chat.lmsys.org/), and many others. One thousand Thanks to all of them! I had to modify the generated result and went through tricky prompting and untraceable debug loops to turn the code suitable for my need.

### Status and Contribution:

All functions in the `main` repository branch are tested and working as far as I noticed. Although the library is in working condition, the library is not complete as of now!

### `#`TODO:

1. Instructions to use the functions provided here have to be documented.

2. Code must be explained under comments.

3. More testing is required.

4. Some harmless but annoying compiler warnings needed to be ironed out.

5. A new development GIT branch has to be created.

Create a pull request or open an issue if you have a recommendation. Please feel free to improve the library project. Remember that the licence term is 'Boost Software Library Licence'.

#### Test program's expected output:

```
Linux llll-H81M-WW 5.15.0-72-generic x86_64
 15:09:23 up  2:46,  1 user,  load average: 0.24, 0.63, 0.85
 ~/D/safe_c   dev  ./buildproj.sh                Sunday 21 May 2023 03:09:24 PM
-- Configuring done
-- Generating done
-- Build files have been written to: /home/llll/Documents/safe_c/build
[ 50%] Building C object CMakeFiles/safe_c.dir/src/main.c.o
In file included from /home/llll/Documents/safe_c/src/main.c:7:
/home/llll/Documents/safe_c/include/sf_c.h: In function ‘sf_getchar’:
/home/llll/Documents/safe_c/include/sf_c.h:591:5: warning: ignoring return value of ‘fgets’ declared with attribute ‘warn_unused_result’ [-Wunused-result]
  591 |     fgets(buf, sizeof(buf), stdin);
In file included from /home/llll/Documents/safe_c/src/main.c:7:
/home/llll/Documents/safe_c/include/sf_c.h: In function ‘sf_cls’:
/home/llll/Documents/safe_c/include/sf_c.h:722:3: warning: ignoring return value of ‘system’ declared with attribute ‘warn_unused_result’ [-Wunused-result]
  722 |   system("clear");
      |   ^~~~~~~~~~~~~~~
In file included from /home/llll/Documents/safe_c/src/main.c:7:
/home/llll/Documents/safe_c/include/sf_c.h: In function ‘sf_holdscr’:
/home/llll/Documents/safe_c/include/sf_c.h:880:3: warning: ignoring return value of ‘system’ declared with attribute ‘warn_unused_result’ [-Wunused-result]
  880 |   system("read ans"); // Linux. command explanation: `read` was used to read from stdin, `-p` means that the user will be prompted for input.  // https://unix.stackexchange.com/questions/293940/how-can-i-make-press-any-key-to-continue
      |   ^~~~~~~~~~~~~~~~~~
[100%] Linking C executable safe_c
[100%] Built target safe_c
Hey! "./safe_c" here!
First argument: (null)
Second argument: SHELL=/bin/bash
                                            test: sf_strcpy
Hello, safety!
                                            test: sf_strncpy
Hello, safety!
                                            test: sf_gets
Type something and hit Enter
Kalu was a black male cat.
You entered: Kalu was a black male cat. Hello, safety!
                                            test: sf_scanf
Enter a number: 1011
You entered: 1011


                                            test: sf_getchar


Enter a character: y
The entered character is : y


                                            test: sf_strcat
Final destination string : |Hello, safety!Hello|                                            test: sf_sprintf
Output:
Kalu was a black male cat. 
character count = 284
                                            test: sf_atoi
string value = Hello, safety!Hello, integer value = 0
C was created in Bell Laboratory
Please choose an option:
1. Clear the screen.
2. Keep the screen as it is.
                                            test: sf_scanf
2
Keeping the screen as it is.
                                            test: sf_holdscr
Press any key to continue...

                                            test: sf_puts
Hello, Safety! puts 
                                            test: sf_puts
Error message! 
                                            test: sf_getc
File contains 13 r.
                                            test: sf_strtok
                                            test: sf_strtok
 Wikipedia: Dark matter is a hypothetical form of matter thought to account for approximately 85% of the matter in the universe!!!
  Dark matter is called "dark" because it does not appear to interact with the electromagnetic field, which means it does not absorb, reflect, or emit electromagnetic radiation and is, therefore, difficult to detect!!!
  Most experts think that dark matter is abundant in the universe and has had a strong influence on its structure and evolution!!!
                                            test: sf_strtok
                                            test: sf_strtok
 apple
 banana
 carrot
                                            test: vsprintf_test
123 < 456 
                                            test: vsprintf_test
This is a string 
                                            test: sf_putc
See the contents of the file "testfile2.txt"
                                            test: sf_putchar
123456789
                                            test: sf_strcpy
                                            test: sf_puts
deststr: before memcpy:   
                                            test: sf_puts
Emulator! 
                                            test: sf_memcpy
                                            test: sf_puts
deststr: after sf_memcpy:   
                                            test: sf_puts
Terminal 

                                            test: sf_strdup
strdupTest
                                            test: sf_strndup
strNdup
                                            test: fputs
                                            test: sf_fscanf
Read String1 |We|
Read String2 |are|
Read String3 |testing|
Read String4 |fscanfTest|
Writing "HereIsMyName: Appu." onto buffer with capacity 15
                                            test: sf_snprintf
String written on buffer = "HereIsMyName:
Value returned by sf_snprintf() method = 22
                                            test: sf_strcpy
                                            test: sf_sscanf
March 25, 1989 = Saturday
                                            test: sf_strcat
                                            test: sf_strcat
Pinaki 
Gupta
Pinaki Gupta
see the output file textfile4.txt
                                            test: sf_strchr
String after |,| is - |, free, online encyclopedia written and maintained by a community of volunteers.|
                                            test: sf_strncat
HelloChatGPT
                                            test: sf_holdscr
Press any key to continue...

                                            test: sf_assert
Assertion failed: x > 10
 !  ~/D/safe_c   dev         
```

#### Untested but available functions:

```

```

#### Tested:

```
(done) getchar() (tested)
(done) sf_holdscr() (tested)
(done) atoi() (tested)
(done) assert() (tested) -> static_assert()
(done) fflush() for input streams (tested)
(done) sprintf() (tested)
(done) puts() (tested) (tested)
(done) getc() (tested)
(done) strdup() (tested)
(done) strndup() (tested)
(done) cls() (tested)
(done) fgets() (tested)
(done) strcpy() (tested) (tested)
(done) strncpy() (tested)
(done) vsnprintf() (tested)
(done) vsprintf() (tested)
(done) gets() (tested)
(done) scanf() (tested)
(done) strlen() (tested)
(done) strtok() (tested)
(done) memset() (tested)
(done) memcpy() (tested)
(done) putc() (tested)
(done) putchar() (tested)
(done) fscanf() (tested)
(done) vfscanf() (tested)
(done) snprintf() (tested)
(done) sscanf() (tested)
(done) strcat() (tested)
(done) vfprintf() (tested)
(done) strchr() (tested)
(done) strncat() (tested)
```

#### Planned:

```
fopen() [Safe. Snippets required.]
fwrite()
fprintf()
fputs()
fputc()
fread()
printf()
setjmp()
longjmp()
signal()
va_start(), va_arg() and va_end().
system() [Sanitisation techniques will be documented.]
makepath -> _makepath_s (MSDN)
_splitpath -> _splitpath_s (MSDN)
```

#### Will be investigated:

```
strlcpy()
strcpy_s()
strlcat()
strcat_s()
gets_s()
_sprintf()
```

---

# Licence:

BSL 1.0

```
Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
```
