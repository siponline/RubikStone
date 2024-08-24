#include <stdio.h>  
#include <stdint.h>  
#include <string.h>  
#include <stdlib.h>  
#include <math.h>
#include <time.h> 
#include "fast_lookup.h"  
#include "RubikStone_128_16_16_16_demo.h" 
  
#define BLOCK_SIZE 16  //how many bytes of a cipher block
#define Round 16   //how many rounds of a cipher
unsigned long table_size=65536;  //how many entries in a table
unsigned long entry_size=8;   //how many bytes of an entry
unsigned long total_tables=16;   //how many tables in total
  
typedef uint8_t byte;  
typedef byte block[BLOCK_SIZE]; 

void uint64_to_uint8_array(uint64_t value, uint8_t *arr) {
    int i;
	for (i = 0; i < 8; i++) {
        arr[i] = (value >> (8 * (7 - i))) & 0xFF;
    }
}

void roundFunction(block left, block right) {  
	int i;	
    for (i = 0; i < BLOCK_SIZE / 2; i++,i++) {  
        byte leftByte1 = left[i]; 
		byte leftByte2 = left[i+1]; 
		
		// Select a lookup table based on randomly generated guidance key
	    unsigned long random_number = rand(); 
		unsigned long guidance_key=random_number%total_tables; 
		
		char filename[100];
		sprintf(filename, "in%d_out%d_lut%d.bin", (int)log2(table_size),entry_size*8,guidance_key);
		printf("Selected table:  %s\n", filename);
		  
		
	    uint64_t entry = fast_lookup(filename, (uint16_t)(leftByte1<< 8)|leftByte2, table_size, entry_size);
		printf("Entry at index %d: 0x%llx\n", (uint16_t)(leftByte1<< 8)|leftByte2, (unsigned long long)entry);  
        
        uint8_t lutOutput[8];
		uint64_to_uint8_array(entry, lutOutput);
        
        int j;
		for (j = 0; j < 8; j++) {  
            right[j] = right[j] ^ lutOutput[j];  
        }    
    }  
}  

void feistelCipher(block plaintext, block ciphertext) {  
    block left, right;  
  
    memcpy(left, plaintext, BLOCK_SIZE / 2);  
    memcpy(right, plaintext + BLOCK_SIZE / 2, BLOCK_SIZE / 2); 

	int r;
    for (r = 0; r < Round; r++) { 
		printf("\n\n=========the %d-th round==========\n",r); 
        roundFunction(left, right);  
        
        byte temp[BLOCK_SIZE / 2];  
        memcpy(temp, left, BLOCK_SIZE / 2);  
        memcpy(left, right, BLOCK_SIZE / 2);  
        memcpy(right, temp, BLOCK_SIZE / 2);
        int i;
        printf("leftblock: ");
		for (i = 0; i < BLOCK_SIZE / 2; i++) {  
	        printf("%02X ", left[i]);  
	    } 
	    printf("\nrightblock: ");
	    for (i = 0; i < BLOCK_SIZE / 2; i++) {  
	        printf("%02X ", right[i]);  
	    } 
	    printf("\n");  
    }  
    memcpy(ciphertext, left, BLOCK_SIZE / 2);  
    memcpy(ciphertext + BLOCK_SIZE / 2, right, BLOCK_SIZE / 2);  
}  
  
int RubikStone_128_16_16_16_demo() {  

    block plaintext;
    
    printf("Please enter %d numbers of type uint8_t (0-255), each number followed by a space or a line break£º\n", BLOCK_SIZE);
  
    int i;
	for (i = 0; i < BLOCK_SIZE; i++) {  
        if (scanf("%hhu", &plaintext[i]) != 1) {    
            printf("Input error, please enter a valid uint8_t number (0-255)\n"); 
            while (getchar() != '\n');  
            i--; 
        }  
    }   

    block ciphertext;  
    srand(time(NULL)); // Initialize random number seed
    feistelCipher(plaintext, ciphertext);  
    
    printf("Plaintext£º\n");  
    for (i = 0; i < BLOCK_SIZE; i++) {  
        printf("%02X ", plaintext[i]);  
    }  
    printf("\n");
    
    printf("Ciphertext: ");  
    for (i = 0; i < BLOCK_SIZE; i++) {  
        printf("%02X ", ciphertext[i]);  
    }  
    printf("\n"); 

  
    return 0;  
}
