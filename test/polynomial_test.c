#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "../debug.h"
#include "../gf.h"
#include "../polynomial.h"

void test_1() {
  POLYNOMIAL* x;
  uint16_t x_data[] = {1, 2, 3, 4, 5, 6};
  uint16_t x_length = 6;

  printf(" --- test 1 --- \n> Polinomial pretty printing\n");

  x = (POLYNOMIAL*) malloc(sizeof(POLYNOMIAL));
  if (x == NULL) {
    error("Failed to allocate memory for x POLYNOMIAL!\nExiting...");
    exit(MEM_ERROR);
  }
  POLY_init(x, x_data, x_length);
  POLY_pretty_print(x);
  POLY_free(x);

  printf(" --- end test --- \n\n");
}

void test_2() {
  POLYNOMIAL* x;
  POLYNOMIAL* y;
  uint16_t x_data[] = {0, 1, 0, 1}; /* x^3 + x */
  uint16_t x_length = 4;
  uint16_t y_data[] = {1, 0, 1, 1}; /* x^3 + x^2 + 1 */
  uint16_t y_length = 4;
  GF_PARAMS* params;
  POLYNOMIAL* result;

  printf(" --- test 2 --- \n> Polinomial multiplication\n");

  params = malloc(sizeof(GF_PARAMS));
  params->m = 4;
  params->t = 2;
  params->generator = 0;
  GF_init(params);

  x = (POLYNOMIAL*) malloc(sizeof(POLYNOMIAL));
  if (x == NULL) {
    error("Failed to allocate memory for x POLYNOMIAL!\nExiting...");
    exit(MEM_ERROR);
  }
  POLY_init(x, x_data, x_length);
  POLY_pretty_print(x);
  y = (POLYNOMIAL*) malloc(sizeof(POLYNOMIAL));
  if (y == NULL) {
    error("Failed to allocate memory for y POLYNOMIAL!\nExiting...");
    exit(MEM_ERROR);
  }
  POLY_init(y, y_data, y_length);
  POLY_pretty_print(y);

  result = POLY_mul(x, y, params);
  POLY_pretty_print(result);

  POLY_free(result);
  POLY_free(x);
  POLY_free(y);
 
  printf(" --- end test --- \n\n");
}

void test_3() {
  POLYNOMIAL* x;
  POLYNOMIAL* y;
  uint16_t x_data[] = {1, 7, 14, 8}; /* x^3 + 7*x^2 + 14*x + 8 */
  uint16_t x_length = 4;
  uint16_t y_data[] = {1, 8}; /* x + 8 */
  uint16_t y_length = 2;
  GF_PARAMS* params;
  POLYNOMIAL* result; /* should be: 1, 15, 3, 1, 12 (big-endian)*/

  printf(" --- test 3 --- \n> Polinomial multiplication\n");

  params = malloc(sizeof(GF_PARAMS));
  params->m = 4;
  params->t = 2;
  params->generator = 0;
  GF_init(params);

  x = (POLYNOMIAL*) malloc(sizeof(POLYNOMIAL));
  if (x == NULL) {
    error("Failed to allocate memory for x POLYNOMIAL!\nExiting...");
    exit(MEM_ERROR);
  }
  POLY_init(x, x_data, x_length);
  POLY_pretty_print(x);
  y = (POLYNOMIAL*) malloc(sizeof(POLYNOMIAL));
  if (y == NULL) {
    error("Failed to allocate memory for y POLYNOMIAL!\nExiting...");
    exit(MEM_ERROR);
  }
  POLY_init(y, y_data, y_length);
  POLY_pretty_print(y);

  result = POLY_mul(x, y, params);
  POLY_pretty_print(result);

  POLY_free(result);
  POLY_free(x);
  POLY_free(y);
 
  printf(" --- end test --- \n\n");
}

void test_4() {
  POLYNOMIAL* x;
  POLYNOMIAL* y;
  //uint16_t x_data[] = {0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  
  // result: 3*x^3 + 3*x^2 + 12*x^1 + 12*x^0
  //uint16_t x_data[] = {0, 0, 0, 0, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

  // result: 4*x^3 + 13*x^2 + 10*x^1 + 1*x^0
  uint16_t x_data[] = {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2}; 

  uint16_t x_length = 15;
  //uint16_t y_data[] = {12, 1, 3, 15, 1}; // generator element = 2
  uint16_t y_data[] = {10, 1, 2, 8, 1}; // generator element = 3
  uint16_t y_length = 5;
  GF_PARAMS* params;
  POLYNOMIAL* result;

  printf(" --- test 4 --- \n> Polinomial modular division\n");

  params = malloc(sizeof(GF_PARAMS));
  params->m = 4;
  params->t = 2;
  params->generator = 0;
  GF_init(params);

  x = (POLYNOMIAL*) malloc(sizeof(POLYNOMIAL));
  if (x == NULL) {
    error("Failed to allocate memory for x POLYNOMIAL!\nExiting...");
    exit(MEM_ERROR);
  }
  POLY_init(x, x_data, x_length);
  POLY_pretty_print(x);
  y = (POLYNOMIAL*) malloc(sizeof(POLYNOMIAL));
  if (y == NULL) {
    error("Failed to allocate memory for y POLYNOMIAL!\nExiting...");
    exit(MEM_ERROR);
  }
  POLY_init(y, y_data, y_length);
  POLY_pretty_print(y);

  result = POLY_rem(x, y, params);
  POLY_pretty_print(result);

  POLY_free(result);
  POLY_free(x);
  POLY_free(y);

  printf(" --- end test --- \n\n");

}

int main(int argc, char const *argv[]) {
  
  test_1();
  test_2();
  test_3();
  test_4();

  return 0;
}