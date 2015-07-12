#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#define DEFAULT_DEGREE_VALUE (300)
#define COEFF_TYPE uint16_t

struct POLYNOMIAL {
  COEFF_TYPE*  coeff;
  uint16_t     degree;
};
typedef struct POLYNOMIAL POLYNOMIAL;

void POLY_init(POLYNOMIAL* p, COEFF_TYPE* coeff, uint16_t length);
void POLY_free(POLYNOMIAL* p);
void POLY_pretty_print(POLYNOMIAL* p);
void POLY_print(POLYNOMIAL* p);
POLYNOMIAL* POLY_mul(POLYNOMIAL* x, POLYNOMIAL* y, GF_PARAMS* params);
POLYNOMIAL* POLY_rem(POLYNOMIAL* x, POLYNOMIAL* y, GF_PARAMS* params);


#endif /* POLYNOMIAL_H */