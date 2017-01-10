#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#define BUF_SIZE 51200000

void move_spaces_brute(char *str, size_t len) {
  for (size_t i=0; i<len; i++) {
    if (str[i] == ' ') {
      for (size_t j=i; j>0; j--) {
        str[j] = str[j-1];
      }
      str[0] = ' ';
    }
  }
}

void move_spaces_opt(char *str, size_t len) {
  char *rp = str + len;
  char *wp = rp;
  do {
    rp--;
    if (*rp != ' ') {
      wp--;
      *wp = *rp;
    }
  } while (rp != str);
  do {
    wp--;
    *wp = ' ';
  } while (wp != str);
}

int main() {

  void *buffer;
  char *filename = "string.txt";
  buffer = malloc(BUF_SIZE);
  assert(buffer != NULL);

  FILE* file = fopen(filename, "r");
  size_t len = fread(buffer, 1, BUF_SIZE, file);

  char *ref = (char*) buffer;
  char *str = calloc(len, sizeof(char));
  clock_t start, stop;
  double duration;

  for (size_t i=0; i<len; i++) {
    str[i] = ref[i];
  }
  start = clock();
  move_spaces_brute(str, len);
  stop = clock();
  duration = 1000.0 * (stop - start) / CLOCKS_PER_SEC;
  printf("Brute : %f ms, text : \"%s\"\n", duration, str);

  for (size_t i=0; i<len; i++) {
    str[i] = ref[i];
  }
  start = clock();
  move_spaces_opt(str, len);
  stop = clock();
  duration = 1000.0 * (stop - start) / CLOCKS_PER_SEC;
  printf("Opt : %f ms, text : \"%s\"\n", duration, str);

  free(str);
}
