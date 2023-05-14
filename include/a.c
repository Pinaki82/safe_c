#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>  // for size_t, sf_strchr()
#include <string.h>
// https://learn.microsoft.com/en-us/cpp/c-runtime-library/file-constants?view=msvc-170
#include <fcntl.h>
#include <stdarg.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <stdint.h> // for uint8_t

size_t bard_vsnprintf(char *buffer, size_t size, const char *format, va_list args);
size_t bard_vsnprintf(char *buffer, size_t size, const char *format, va_list args) {
  size_t written = 0;

  while(*format) {
    if(*format == '%') {
      format++;

      switch(*format) {
        case 'c':
          buffer[written++] = va_arg(args, int);
          break;

        case 's': {
            char *s = va_arg(args, char *);
            size_t len = strlen(s);

            if(len > size - written) {
              len = size - written;
            }

            memcpy(buffer + written, s, len);
            written += len;
          }
          break;

        case '%':
          buffer[written++] = '%';
          break;

        default:
          // Unknown format specifier.
          return (size_t)(-1);
      }
    }

    else {
      buffer[written++] = *format; // SEGFAULT: GDB tracebak sf_sprintf() -> bard_vsnprintf()
    }

    format++;
  }

  buffer[written] = '\0';
  return written;
}
