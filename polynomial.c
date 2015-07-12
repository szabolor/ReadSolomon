#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include "gf.h"
#include "debug.h"
#include "polynomial.h"

/*
  POLY_init: initialize the polynom with the given data as coefficients
             the last data would be the highest degree among the coeffs
             the certain degrees represented by the coeff array indexes
*/
void POLY_init(POLYNOMIAL* p, COEFF_TYPE* coeff, uint16_t length) {
  assert( length > 0 );
  p->degree = length - 1;
  p->coeff = (COEFF_TYPE*) calloc(length, sizeof(COEFF_TYPE));
  if (p->coeff == NULL) {
    error("Failed to allocate memory for p->coeff\nExiting...");
    exit(MEM_ERROR);
  }
  memcpy(p->coeff, coeff, length * sizeof(COEFF_TYPE));
}

void POLY_free(POLYNOMIAL* p) {
  if (p) {
    if (p->coeff) {
      free(p->coeff);
    }
    free(p);
  }
}

void POLY_pretty_print(POLYNOMIAL* p) {
  int i;
  if (p && p->coeff) {
    printf("Degree: %d\n", p->degree);
    for (i = p->degree; i > 0; --i) {
      printf("%d*x^%d + ", p->coeff[i], i);
    }
    printf("%d\n\n", p->coeff[0]);
  } else {
    error("There's an uninitialized polynomial p given!\n");
  }
}

/*
  POLY_mul: return the two polynomial multiplication
*/
POLYNOMIAL* POLY_mul(POLYNOMIAL* x, POLYNOMIAL* y, GF_PARAMS* params) {
  POLYNOMIAL* result;
  uint16_t i, j, tmp;

  result = (POLYNOMIAL*) malloc(sizeof(POLYNOMIAL));
  if (result == NULL) {
    error("Failed to allocate memory for p POLYNOMIAL!\nExiting...");
    exit(MEM_ERROR);
  }
  result->degree = x->degree + y->degree;
  result->coeff = (COEFF_TYPE*) calloc(result->degree + 1, sizeof(COEFF_TYPE));
  if (result->coeff == NULL) {
    error("Failed to allocate memory for result->coeff\nExiting...");
    exit(MEM_ERROR);
  }
  for (i = 0; i <= x->degree; ++i) {
    for (j = 0; j <= y->degree; ++j) {
      tmp = GF_mul(
        x->coeff[x->degree - i],
        y->coeff[y->degree - j],
        params
      );
/*
      printf("GF_mul(x[%d]=%d, y[%d]=%d) = %d\t\t", x->degree - i, x->coeff[x->degree - i], y->degree - j, y->coeff[y->degree - j], tmp);
      printf("GF_add(%d, r[%d]=%d) = ", tmp, x->degree - i + y->degree - j, result->coeff[x->degree - i + y->degree - j]);
*/    
      result->coeff[x->degree - i + y->degree - j] = GF_add(
        tmp,
        result->coeff[x->degree - i + y->degree - j]
      );
/*      printf("%d\n", result->coeff[x->degree - i + y->degree - j]); */
    }
  }
  return result;
}

/*
  POLY_rem: return `x mod y`
*/
POLYNOMIAL* POLY_rem(POLYNOMIAL* x, POLYNOMIAL* y) {

}