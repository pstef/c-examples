/* itoa() implementation. Concept by Zhivago, my additions. */

#include <stdio.h>
 
char *itoa(char *buffer, size_t size, int v, unsigned char base) {
  static const char hex[16] = "0123456789ABCDEF";
  unsigned int i;
 
  if (size <= 1 || base > sizeof hex)
    return NULL;
 
  buffer += size--;
  *--buffer = '\0';
 
  i = v;
 
  if (v < 0) {
    i = (-1U) - i + 1;
  }
 
  while (size > 0) {
    *--buffer = hex[i % base];
    size--;
    i /= base;
    if (i == 0) {
      if (v < 0) {
        if (size > 0) {
          *--buffer = '-';
        } else {
          break; 
        }
      }
      return buffer;
    }
  }
  return NULL;
}
 
#include <stdlib.h>
#include <limits.h>
#include <math.h>
 
int main(void) {
  char buffer[12], buffer2[32], *converted;
  printf("Printf: %i\n", INT_MIN);
  if ((converted = itoa(buffer, sizeof buffer, INT_MIN, 10)))
    puts(converted);
  printf("Printf: %i\n", INT_MAX);
  if ((converted = itoa(buffer, sizeof buffer, INT_MAX, 10)))
    puts(converted);
  if ((converted = itoa(buffer2, sizeof buffer2, 1500100900, 16)))
    puts(converted);
  if ((converted = itoa(buffer2, sizeof buffer2, 1500100900, 2)))
    puts(converted);

  int value = -0xBC614E;
  unsigned char base = 10;
  char howmany[(value < 0) + 1 + 1 + (unsigned int) (log(abs(value)) / log(base))];
  printf("Size: %zu\n", sizeof howmany);
  if ((converted = itoa(howmany, sizeof howmany, value, base)))
    puts(converted);
  return 0;
}
