/* Zhivago's itoa() implemented with an FSM */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
 
struct emit {
  void (*emitter)(struct emit *out, char value);
};
 
void emit(struct emit *out, char value) {
  out->emitter(out, value);
}
 
void uitoat(struct emit *out, unsigned int value, unsigned char base) {
  unsigned char digit = value % base;
  if (digit > 0) {
    uitoat(out, value / base, base);
    emit(out, "0123456789ABCDEF"[digit]);
  }
}
 
void uitoa(struct emit *out, unsigned int value, unsigned char base) {
  unsigned char digit = value % base;
  if (digit > 0) {
    uitoat(out, value / base, base);
  }
  emit(out, "0123456789ABCDEF"[digit]);
}
 
void itoa(struct emit *out, int value, unsigned char base) {
  if (value < 0) {
    emit(out, '-');
    uitoa(out, (-1U) - value + 1, base);
  } else {
    uitoa(out, value, base);
  }
}
 
struct emit_to_string {
  struct emit emit;
  char *string;
  size_t space;
  size_t used;
};
 
void emit_to_string(struct emit *base, char value) {
  struct emit_to_string *out = (void *)base;
  if (out->space > 0) {
    out->space -= 1;
    *out->string++ = value;
  }
  out->used += 1;
}
 
int main() {
  char buffer[100];
  struct emit_to_string to_string = { { emit_to_string }, buffer, sizeof buffer, 0 };
  struct emit *out = (void *)&to_string;
  itoa(out, 12345, 10);
  emit(out, ',');
  itoa(out, -12345, 10);
  emit(out, ',');
  itoa(out, 0, 10);
  emit(out, '\0');
  if (to_string.used < sizeof buffer) {
    puts(buffer);
  }
  return 0;
}
