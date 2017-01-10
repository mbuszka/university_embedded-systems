#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <time.h>

#define BUF_SIZE 512000000

int popcount(uint16_t i) {
  int c;
  for (c=0; i; i >>= 1) c += i & 1;
  return c;
}

char *prepare_precalc_8() {
  char *table = calloc(256, 1);
  for (unsigned int i = 0u; i < 256u; i++)
    table[i] = popcount((uint16_t) i);
  return table;
}

char *prepare_precalc_16() {
  char *table = calloc(65536, 1);
  for (unsigned int i = 0u; i < 65536u; i++)
    table[i] = popcount((uint16_t) i);
  return table;
}

size_t calculate_precalc_8(void *buffer, int n) {
  char *table = prepare_precalc_8();
  unsigned char *buf = (unsigned char*) buffer;
  size_t count = 0;
  for (int i=0; i<n; i++)
    count += table[buf[i]];
  return count;
}

size_t calculate_precalc_16(void *buffer, int n) {
  char   *table = prepare_precalc_16();
  uint16_t *buf = (uint16_t*) buffer;
  size_t count = 0;
  int m = n/2;
  for (int i=0; i<m; i++)
    count += table[buf[i]];
  return count + (n%2 ? popcount(((char*) buffer)[n]) : 0);
}

size_t calculate_popcount(void *buffer, int n) {
  uint16_t *buf = (uint16_t*) buffer;
  int m = n/2;
  size_t count = 0;
  for (int i=0; i<m; i++)
    count += popcount(buf[i]);
  return count + (n%2 ? popcount(((char*) buffer)[n]) : 0);
}

int main() {
  void *buffer;
  char *filename = "data.bin";
  buffer = malloc(BUF_SIZE);
  assert(buffer != NULL);

  FILE* file = fopen(filename, "rb");
  size_t n = fread(buffer, 1, BUF_SIZE, file);

  clock_t start, stop;
  size_t count;
  double duration;

  start = clock();
  count = calculate_precalc_8(buffer, n);
  stop  = clock();
  duration = 1000.0 * (stop - start) / CLOCKS_PER_SEC;
  printf("Precalc 8 bit : %f ms, result : %lu\n", duration, count);

  start = clock();
  count = calculate_precalc_16(buffer, n);
  stop  = clock();
  duration = 1000.0 * (stop - start) / CLOCKS_PER_SEC;
  printf("Precalc 16 bit : %f ms, result : %lu\n", duration, count);

  start = clock();
  count = calculate_popcount(buffer, n);
  stop  = clock();
  duration = 1000.0 * (stop - start) / CLOCKS_PER_SEC;
  printf("Bitmask 16 bit : %f ms, result : %lu\n", duration, count);

  free(buffer);
}
