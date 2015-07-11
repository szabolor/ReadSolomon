#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "rs_encoder.h"
#include "debug.h"
#include "gf.h"

int main(int argc, char const *argv[]) {
  GF_PARAMS* params;

  params = malloc(sizeof(GF_PARAMS));
  params->m = 8;
  params->t = 16;
  params->generator = 0;

  GF_init(params);

  return 0;
}