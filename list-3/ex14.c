#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <assert.h>

#define BUF_SIZE 512000000

int condition_brute(unsigned int n) {
  int c;
  for (c=0; n; n >>= 1) c += n & 1;
  return c > 1;
}

int condition_opt(unsigned int n) {
  return n & (n-1);
}

int main() {
  void *buffer;
  char *filename = "data.bin";
  buffer = malloc(BUF_SIZE);
  assert(buffer != NULL);

  FILE* file = fopen(filename, "rb");
  size_t n = fread(buffer, 1, BUF_SIZE, file);
  unsigned int *data = (unsigned int*) buffer;
  int count = n / sizeof(unsigned int);

  size_t res = 0;
  clock_t start, stop;
  double duration;

  res = 0;
  start = clock();
  for (int i=0; i<count; i++)
    res += condition_brute(~data[i]) != 0;
  stop  = clock();
  duration = 1000.0 * (stop - start) / CLOCKS_PER_SEC;
  printf("Brute : %f ms, result : %lu\n", duration, res);

  res = 0;
  start = clock();
  for (int i=0; i<count; i++)
    res += condition_opt(~data[i]) != 0;
  stop  = clock();
  duration = 1000.0 * (stop - start) / CLOCKS_PER_SEC;
  printf("Opt : %f ms, result : %lu\n", duration, res);

  free(buffer);
  return 0;
}
