#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <assert.h>

#define BUF_SIZE 512000000

static const unsigned char bit_rev_table[256] =
{
#   define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64
#   define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#   define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )
    R6(0), R6(2), R6(1), R6(3)
};

uint32_t reverse_brute(uint32_t n) {
  uint32_t res = n;
  int s = 31;
  for (n >>= 1;n;n >>= 1) {
    res <<= 1;
    res |= n & 1;
    s--;
  }
  res <<= s;
  return res;
}

uint32_t reverse_lookup(uint32_t n) {
  return (bit_rev_table[n & 0xff] << 24) |
         (bit_rev_table[(n >> 8) & 0xff] << 16) |
         (bit_rev_table[(n >> 16) & 0xff] << 8) |
         (bit_rev_table[(n >> 24) & 0xff]);
}

uint32_t reverse_divide(uint32_t n) {
  // swap odd and even bits
  n = ((n >> 1) & 0x55555555) | ((n & 0x55555555) << 1);
  // swap consecutine pairs
  n = ((n >> 2) & 0x33333333) | ((n & 0x33333333) << 2);
  // swap nibbles ...
  n = ((n >> 4) & 0x0F0F0F0F) | ((n & 0x0F0F0F0F) << 4);
  // swap bytes
  n = ((n >> 8) & 0x00FF00FF) | ((n & 0x00FF00FF) << 8);
  // swap 2-byte long pairs
  n = ( n >> 16             ) | ( n               << 16);
  return n;
}

int main() {
  uint32_t r;
  clock_t start, stop;
  double duration;

  void *buffer;
  char *filename = "data.bin";
  buffer = malloc(BUF_SIZE);
  assert(buffer != NULL);

  FILE* file = fopen(filename, "rb");
  size_t n = fread(buffer, 1, BUF_SIZE, file) / sizeof(uint32_t);
  uint32_t *tab = (uint32_t *) buffer;

  start = clock();
  for (uint32_t i=0; i<n; i++)
    r = reverse_brute(tab[i]);
  stop = clock();
  duration = 1000.0 * (stop - start) / CLOCKS_PER_SEC;
  printf("Brute : %f ms, result : %u\n", duration, r);

  start = clock();
  for (uint32_t i=0; i<n; i++)
    r = reverse_lookup(tab[i]);
  stop = clock();
  duration = 1000.0 * (stop - start) / CLOCKS_PER_SEC;
  printf("Lookup : %f ms, result : %u\n", duration, r);

  start = clock();
  for (uint32_t i=0; i<n; i++)
    r = reverse_divide(tab[i]);
  stop = clock();
  duration = 1000.0 * (stop - start) / CLOCKS_PER_SEC;
  printf("Divide : %f ms, result : %u\n", duration, r);

}
