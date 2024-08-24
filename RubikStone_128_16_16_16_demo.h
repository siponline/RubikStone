#ifndef RUBIKSTONE_128_16_16_16_DEMO_H
#define RUBIKSTONE_128_16_16_16_DEMO_H

#include <stdint.h>

#define BLOCK_SIZE 16
#define Round 16

typedef uint8_t byte;
typedef byte block[BLOCK_SIZE];

void feistelCipher(block plaintext, block ciphertext);
int RubikStone_128_16_16_16_demo();

#endif // RUBIKSTONE_128_16_16_16_DEMO_H

