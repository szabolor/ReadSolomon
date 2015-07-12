#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "gf.h"
#include "debug.h"

#define EPS (0.0001)

uint16_t GF_get_generator_for_m(uint16_t m) {
  switch (m) {
    case 1: return 3; break;
    case 2: return 7; break;
    case 3: return 11; break;
    case 4: return 19; break;
    case 5: return 37; break;
    case 6: return 67; break;
    case 7: return 131; break;
    case 8: return 285; break;
    default:
      debug("There's no build-in generator for %d bit length", m);
      exit(1);
  }
}

void GF_init(GF_PARAMS* params) {
  if (params->t == 0) {
    debug("Wrong GF_PARAMS data: Zero for 't' (symbol correction number)\n t=2 will be used by default");
    params->t = 2;
  }
  if (params->m == 0) {
    debug("Wrong GF_PARAMS data: Zero for 'm' (symbol bit length)\n m=4 will be used by default");
    params->m = 4;
  }
  if (params->generator == 0) {
    params->generator = GF_get_generator_for_m(params->m);
  }

  params->n = (1 << params->m) - 1;
  /* Check for ill-conditioned cases at computing k value */
  assert (params->n > 2 * params->t);
  params->k = params->n - 2 * params->t;

  GF_precompute_tables(params);
}

void GF_precompute_tables(GF_PARAMS* params) {
  uint16_t i;

  //debug("n: %d", params->n);

  params->alpha_by_num = (uint16_t*) malloc(params->n * sizeof(uint16_t));
  if (params->alpha_by_num == NULL) {
    error("Failed to allocate memory for params->alpha_by_num!\nExiting...");
    exit(MEM_ERROR);
  }
  params->num_by_alpha = (uint16_t*) malloc(params->n * sizeof(uint16_t));
  if (params->num_by_alpha == NULL) {
    error("Failed to allocate memory for params->num_by_alpha!\nExiting...");
    exit(MEM_ERROR);
  }

  params->num_by_alpha[0] = 1;
  //for (i = 1; (!(i && params->m)); ++i) {
  for (i = 1; i < params->n; ++i) {
    if (params->num_by_alpha[i-1] - (params->n / 2.0) < EPS) {
      params->num_by_alpha[i] = params->num_by_alpha[i-1] << 1;
    } else {
      params->num_by_alpha[i]  = params->num_by_alpha[i-1] << 1;
      params->num_by_alpha[i] ^= params->generator;
      params->num_by_alpha[i] &= params->n;
    }
  }

  for (i = 0; i < params->n; ++i) {
    params->alpha_by_num[params->num_by_alpha[i] - 1] = i;
  }
}

void GF_free(GF_PARAMS* params) {
  if (params) {
    if (params->num_by_alpha) {
      free(params->num_by_alpha);
    }
    if (params->alpha_by_num) {
      free(params->alpha_by_num);
    }  
    free(params);
  }
}

uint16_t GF_add(uint16_t x, uint16_t y) {
  return x ^ y;
}

uint16_t GF_mul(uint16_t x, uint16_t y, GF_PARAMS* params) {
  uint16_t num = 0;

  if (!(x && y)) {
    return 0;
  }
  num = params->alpha_by_num[x - 1] + params->alpha_by_num[y - 1];
  if (num > params->n) {
    num -= params->n;
  }
  return params->num_by_alpha[num];
}