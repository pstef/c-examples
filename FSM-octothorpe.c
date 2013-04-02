/* Zhivago's FSM */

#include <stdio.h>
#include <stdlib.h>
 
typedef void effector(int);
typedef struct transition transition;
struct transition {
  int state;
  effector *effect;
};
 
typedef enum sigil sigil;
enum sigil { Letter, Octothorpe, NewLine, EndOfFile };
 
sigil sigilify(int c) { 
  switch (c) {
    case '#':  return Octothorpe;
    case '\n': return NewLine;
    case EOF:  return EndOfFile;
    default:   return Letter;
  }
}
 
void emit    (int c) { putchar(c); }
void nothing (int c) { }
void halt    (int c) { exit(EXIT_SUCCESS); }
 
#define T(state, sigil) (((state) << 2) | sigil)
 
int main() {
  transition state = { 0, nothing };
  transition table[] = {
    [T(0, Octothorpe)]={ 1, nothing }, [T(0, Letter)]={ 2, emit },    [T(0, NewLine)]={ 0, emit },    [T(0, EndOfFile)]={ 0, halt },
    [T(1, Octothorpe)]={ 1, nothing }, [T(1, Letter)]={ 1, nothing }, [T(1, NewLine)]={ 0, nothing }, [T(1, EndOfFile)]={ 0, halt },
    [T(2, Octothorpe)]={ 3, nothing }, [T(2, Letter)]={ 2, emit },    [T(2, NewLine)]={ 0, emit },    [T(2, EndOfFile)]={ 0, halt },
    [T(3, Octothorpe)]={ 3, nothing }, [T(3, Letter)]={ 3, nothing }, [T(3, NewLine)]={ 0, emit },    [T(3, EndOfFile)]={ 0, halt },
  };
 
  for (;;) {
    int c = getchar();
    transition new = table[T(state.state, sigilify(c))];
    new.effect(c);
    state = new;
  }
}
