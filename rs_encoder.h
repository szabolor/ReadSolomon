#ifndef RS_ENCODER_H
#define RS_ENCODER_H

/*
  rs_encode_255_233: compute the Reed-Solomon(255,233) encode of the data
    data    - the data to be transformed
    length  - the length of the provided data
    output  - the array of 
*/
int rs_encode_255_233(uint16_t data[], uint16_t length, uint16_t output);

#endif /* RS_ENCODER_H */