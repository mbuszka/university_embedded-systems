#include "Morse.h"

char Morse::decode(int code) {
  return _codes[code - 2];
}
