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
             the first data will be the highest degree among the coeffs
             the certain degrees represented by the coeff array indexes
*/
void POLY_init(POLYNOMIAL* p, COEFF_TYPE* coeff, uint16_t length) {
  uint16_t i;

  assert( length > 0 );
  p->degree = length - 1;
  p->coeff = (COEFF_TYPE*) malloc(length * sizeof(COEFF_TYPE));
  if (p->coeff == NULL) {
    error("Failed to allocate memory for p->coeff\nExiting...");
    exit(MEM_ERROR);
  }
  // Insert elements that the first will be the highest degree 
  for (i = 0; i < length; ++i) {
    p->coeff[i] = coeff[length-1-i];
  }
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
  uint16_t i;
  uint8_t first = 1;

  if (p && p->coeff) {
    printf("Degree: %d\n", p->degree);
    for (i = 0; i <= p->degree; ++i) {
      if (p->coeff[i]) {
        if (first == 0) {
          printf(" + ");
        } else {
          first = 0;
        }
        printf("%d*x^%d", p->coeff[i], p->degree - i);
      }
     
    }
    printf("\n\n", p->coeff[p->degree]);
  } else {
    error("There's an uninitialized polynomial p given!\n");
  }
}

void POLY_print(POLYNOMIAL* p) {
  int i;
  if (p && p->coeff) {
    for (i = 0; i <= p->degree; ++i) {
      printf("%d, ", p->coeff[i], p->degree - i);
    }
    putchar('\n');
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
      tmp = GF_mul(x->coeff[i], y->coeff[j], params);
/*
      printf("GF_mul(x[%d]=%d, y[%d]=%d) = %d\t\t", i, x->coeff[i], j, y->coeff[j], tmp);
      printf("GF_add(%d, r[%d]=%d) = ", tmp, i + j, result->coeff[i + j]);
*/    
      result->coeff[x->degree - i + y->degree - j] = GF_add(
        tmp,
        result->coeff[x->degree - i + y->degree - j]
      );
/*      printf("%d\n", result->coeff[i + j]); */
    }
  }
  return result;
}

/*
  POLY_rem: return `x mod y`
*/
POLYNOMIAL* POLY_rem(POLYNOMIAL* x, POLYNOMIAL* y, GF_PARAMS* params) {
  POLYNOMIAL* r;
  uint16_t i, j, factor, tmp;

  r = (POLYNOMIAL*) malloc(sizeof(POLYNOMIAL));
  if (r == NULL) {
    error("Failed to allocate memory for p POLYNOMIAL!\nExiting...");
    exit(MEM_ERROR);
  }
  r->degree = y->degree;
  r->coeff = (COEFF_TYPE*) malloc((y->degree + 1) * sizeof(COEFF_TYPE));
  if (r->coeff == NULL) {
    error("Failed to allocate memory for r->coeff\nExiting...");
    exit(MEM_ERROR);
  }
  memcpy(r->coeff + 1, x->coeff, (r->degree) * sizeof(COEFF_TYPE));
  for (i = 0; i <= (x->degree - y->degree); ++i) {
    //printf("\n\nR: ");
    // Shift out the first (the most higest) element
    memmove(r->coeff, r->coeff + 1, y->degree * sizeof(COEFF_TYPE));
    // Shift in the last new element
    //printf("x->coeff[%d] = %d\n", x->degree - y->degree - i -1, x->coeff[x->degree - y->degree - i - 1]);
    r->coeff[r->degree] = x->coeff[i + r->degree];
    //POLY_print(r);
    //printf("Y: ");
    // Select the factor to be multiplicated by the divider (kinda Gauss elimination)
    factor = GF_div(r->coeff[0], y->coeff[0], params);
    //printf("factor: %d\n", factor);
    for (j = 0; j <= y->degree; ++j) {
      tmp = GF_mul(y->coeff[j], factor, params);
      //printf("%d, ", tmp);
      r->coeff[j] ^= tmp;
    }
  }

  return r;
}