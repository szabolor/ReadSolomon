#ifndef GF_H
#define GF_H

struct GF_PARAMS {
  uint16_t   n; /* Codeword length. Default it's computed by 2^m-1 but can be set lower values */
  uint16_t   m; /* Bit length of a symbol. Required to be filled */
  uint16_t   k; /* Symbol length in a block */
  uint16_t   t; /* Recoverable symbol error number */
  uint16_t   generator; /* Field generator/Primitive polynom */
  uint16_t*  alpha_by_num; /* LUT for primitive element by its value */
  uint16_t*  num_by_alpha; /* LUT for number by primitive element exponent */
};
typedef struct GF_PARAMS GF_PARAMS;

uint16_t GF_init(GF_PARAMS* params);
uint16_t GF_precompute_tables(GF_PARAMS* params);
uint16_t GFadd(uint16_t x, uint16_t y);
uint16_t GFmul(uint16_t x, uint16_t y, uint16_t n);


#endif /* GF_H */