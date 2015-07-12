#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "../debug.h"
#include "../gf.h"

void test_1() {
  int i;

  printf(" --- test 1 --- \n> Exponent LUT\nm=4, t=2\n");

  GF_PARAMS* params;
  params = malloc(sizeof(GF_PARAMS));
  params->m = 4;
  params->t = 2;
  params->generator = 0;
  GF_init(params);

  printf("a^x - value:\n");
  for (i = 0; i < params->n; ++i) {
    printf("%3d - %3d\n", i, params->num_by_alpha[i]);
  }

  printf("value - a^x:\n");
  for (i = 0; i < params->n; ++i) {
    printf("%3d - %3d\n", i + 1, params->alpha_by_num[i]);
  }

  GF_free(params);

  printf(" --- end test --- \n\n");
}

void test_2() {
  printf(" --- test 2 --- \n> Addition over GF(2^n)\n");

  assert( GF_add(13, 14) == 3); printf("Passed!\n");
  assert( GF_add(3, 4) == 7); printf("Passed!\n");

  printf(" --- end test --- \n\n");
}

void test_3() {
  printf(" --- test 3 --- \n> Multiplication over GF(2^4)\n");

  GF_PARAMS* params;
  params = malloc(sizeof(GF_PARAMS));
  params->m = 4;
  params->t = 2;
  params->generator = 0;
  GF_init(params);

  assert( GF_mul(7, 8, params) == 13); printf("Passed!\n");
  assert( GF_mul(14, 1, params) == 14); printf("Passed!\n");
  assert( GF_mul(0, 10, params) == 0); printf("Passed!\n");
  assert( GF_mul(10, 12, params) == 1); printf("Passed!\n");

  printf(" --- end test --- \n\n");
}

void test_4() {
  printf(" --- test 4 --- \n> Division over GF(2^4)\n");

  GF_PARAMS* params;
  params = malloc(sizeof(GF_PARAMS));
  params->m = 4;
  params->t = 2;
  params->generator = 0;
  GF_init(params);

  assert( GF_div(13, 8, params) == 7); printf("Passed!\n");
  assert( GF_div(14, 1, params) == 14); printf("Passed!\n");
  assert( GF_div(0, 10, params) == 0); printf("Passed!\n");

  printf(" --- end test --- \n\n");
}

int main(int argc, char const *argv[]) {
  
  test_1();
  test_2();
  test_3();
  test_4();

  return 0;
}