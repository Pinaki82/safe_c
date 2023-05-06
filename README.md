# safe_c

Set of Custom C Functions that are Safe Alternatives.

#### Untested but available functions:

```
(done) fscanf()
(done) snprintf()
(done) sscanf()
(done) strcat()
(done) vfprintf()
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
```

#### Planned:

```
fopen() [Already safe. Snippets required.]
strncat()
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
system() [Sanitisation techniques required to be mentioned.]
makepath -> _makepath_s (MSDN)
_splitpath -> _splitpath_s (MSDN)
```

#### Needs to be investigated:

```
strlcpy()
strcpy_s()
strlcat()
strcat_s()
gets_s()
_sprintf()
```
