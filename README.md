# safe_c

Set of Custom **C Functions** that are **Safe Alternatives**.

# What is it?

Compare the two following programs.

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

```
./test
Enter a string: catos
size is: 5, string is: cato
```

The version of the function `gets()` with the `sf_` prefix (i.e., `sf_gets()`) seems to be more secure. Not?

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
