#include <stdio.h>  
  
int compiler_demo() { 
 
    FILE *fp;  
  
 
    fp = fopen("Compiler_output.c", "w");  
    if (fp == NULL) {  
        perror("Error opening file");  
        return -1;  
    }  
  

    fprintf(fp, "#include <stdio.h>\n");  
    fprintf(fp, "#include <stdint.h>\n");  
    fprintf(fp, "#include <string.h>\n");  
    fprintf(fp, "#include <stdlib.h>\n");  
    fprintf(fp, "#include <time.h>\n"); 
	fprintf(fp, "#include <math.h>\n\n");  
  
    fprintf(fp, "#define BLOCK_SIZE %d\n",16);
    fprintf(fp, "#define Round %d\n\n",16); 
	fprintf(fp, "unsigned long table_size=65536;\n");
	fprintf(fp, "unsigned long entry_size=8; \n");
	fprintf(fp, "unsigned long total_tables=16; \n");
 
    fprintf(fp, "typedef uint8_t byte;\n");  
    fprintf(fp, "typedef byte block[BLOCK_SIZE];\n\n");  
    
	fprintf(fp, "uint64_t fast_lookup(const char *filename, size_t index, size_t table_size, size_t entry_size) { \n");  
	fprintf(fp, "    if (index >= table_size) {  \n"); 
	fprintf(fp, "        fprintf(stderr, \"Index out of range\\n\"); \n");  
	fprintf(fp, "        exit(EXIT_FAILURE);  \n"); 
	fprintf(fp, "    }  \n"); 
	fprintf(fp, "  \n"); 
    fprintf(fp, "	 FILE *file = fopen(filename, \"rb\");  \n"); 
    fprintf(fp, "    if (file == NULL) {  \n"); 
    fprintf(fp, "        perror(\"Failed to open file\");  \n"); 
    fprintf(fp, "        exit(EXIT_FAILURE);  \n"); 
    fprintf(fp, "    }  \n"); 
    fprintf(fp, "\n"); 
    fprintf(fp, "   off_t offset = index * entry_size; \n");  
    fprintf(fp, "  \n"); 
    fprintf(fp, "    if (fseek(file, offset, SEEK_SET) != 0) { \n");  
    fprintf(fp, "        perror(\"Failed to seek in file\");  \n"); 
    fprintf(fp, "        fclose(file);  \n"); 
    fprintf(fp, "        exit(EXIT_FAILURE);  \n"); 
    fprintf(fp, "    }  \n"); 
    fprintf(fp, "\n"); 
    fprintf(fp, "    uint64_t entry; \n");  
    fprintf(fp, "    if (fread(&entry, entry_size, 1, file) != 1) {  \n"); 
    fprintf(fp, "        fprintf(stderr, \"Failed to read entry from file\\n\");\n");   
    fprintf(fp, "        fclose(file);  \n"); 
    fprintf(fp, "        exit(EXIT_FAILURE);  \n"); 
    fprintf(fp, "    }  \n"); 
    fprintf(fp, "    \n"); 
    fprintf(fp, "    fclose(file);\n");   
    fprintf(fp, "\n"); 
    fprintf(fp, "    return entry;  \n"); 
    fprintf(fp, "}\n"); 
    fprintf(fp, "\n"); 
    fprintf(fp, "void uint64_to_uint8_array(uint64_t value, uint8_t *arr) {\n"); 
    fprintf(fp, "    int i;\n"); 
    fprintf(fp, "	 for (i = 0; i < 8; i++) {\n"); 
    fprintf(fp, "       arr[i] = (value >> (8 * (7 - i))) & 0xFF;\n"); 
    fprintf(fp, "    }\n"); 
    fprintf(fp, "}\n"); 
    fprintf(fp, "\n"); 
    fprintf(fp, "void roundFunction(block left, block right) {  \n"); 
    fprintf(fp, "    int i;\n"); 	
    fprintf(fp, "    for (i = 0; i < BLOCK_SIZE / 2; i++,i++) { \n");  
    fprintf(fp, "        byte leftByte1 = left[i]; \n"); 
    fprintf(fp, "	     byte leftByte2 = left[i+1]; \n"); 
    fprintf(fp, "\n"); 
    fprintf(fp, "	     unsigned long random_number = rand();\n");  
    fprintf(fp, "	     unsigned long guidance_key=random_number%%total_tables; \n"); 
    fprintf(fp, "\n"); 
    fprintf(fp, "	     char filename[100];\n"); 
    fprintf(fp, "	     sprintf(filename, \"in%%d_out%%d_lut%%d.bin\", (int)log2(table_size),entry_size*8,guidance_key);\n"); 
    fprintf(fp, "\n"); 
    fprintf(fp, "	     uint64_t entry = fast_lookup(filename, (uint16_t)(leftByte1<< 8)|leftByte2, table_size, entry_size); \n"); 
    fprintf(fp, "\n"); 
    fprintf(fp, "        uint8_t lutOutput[8];\n"); 
    fprintf(fp, "	     uint64_to_uint8_array(entry, lutOutput);\n"); 
    fprintf(fp, "\n"); 
    fprintf(fp, "        int j;\n"); 
    fprintf(fp, "        for (j = 0; j < 8; j++) {  \n"); 
    fprintf(fp, "            right[j] = right[j] ^ lutOutput[j];  \n"); 
    fprintf(fp, "        }    \n"); 
    fprintf(fp, "    }  \n"); 
    fprintf(fp, "}  \n"); 
    fprintf(fp, "\n"); 
    fprintf(fp, "void feistelCipher(block plaintext, block ciphertext) {  \n"); 
    fprintf(fp, "    block left, right;  \n"); 
    fprintf(fp, " \n"); 
    fprintf(fp, "    memcpy(left, plaintext, BLOCK_SIZE / 2);  \n"); 
    fprintf(fp, "    memcpy(right, plaintext + BLOCK_SIZE / 2, BLOCK_SIZE / 2); \n"); 
    fprintf(fp, "\n"); 
    fprintf(fp, "	 int r;\n"); 
    fprintf(fp, "    for (r = 0; r < Round; r++) { \n"); 
    fprintf(fp, "        roundFunction(left, right);  \n"); 
    fprintf(fp, "\n"); 
    fprintf(fp, "        byte temp[BLOCK_SIZE / 2];  \n"); 
    fprintf(fp, "        memcpy(temp, left, BLOCK_SIZE / 2);  \n"); 
    fprintf(fp, "        memcpy(left, right, BLOCK_SIZE / 2);  \n"); 
    fprintf(fp, "        memcpy(right, temp, BLOCK_SIZE / 2); \n"); 
    fprintf(fp, "    } \n"); 
    fprintf(fp, "    memcpy(ciphertext, left, BLOCK_SIZE / 2);  \n"); 
    fprintf(fp, "    memcpy(ciphertext + BLOCK_SIZE / 2, right, BLOCK_SIZE / 2);  \n"); 
    fprintf(fp, "}\n"); 
    fprintf(fp, "\n"); 
    fprintf(fp, "int main() {\n"); 
    fprintf(fp, "\n"); 
    fprintf(fp, "    block plaintext;\n"); 
    fprintf(fp, "    \n"); 
    fprintf(fp, "    printf(\"Please enter %%d numbers of type uint8_t (0-255), each number followed by a space or a line break£º\\n\", BLOCK_SIZE);\n"); 
    fprintf(fp, " \n"); 
    fprintf(fp, "    int i;\n"); 
    fprintf(fp, "	 for (i = 0; i < BLOCK_SIZE; i++) {  \n"); 
    fprintf(fp, "        if (scanf(\"%%hhu\", &plaintext[i]) != 1) {    \n"); 
    fprintf(fp, "            printf(\"Input error, please enter a valid uint8_t number (0-255)\\n\"); \n"); 
    fprintf(fp, "            while (getchar() != '\\n');  \n"); 
    fprintf(fp, "            i--; \n"); 
    fprintf(fp, "        }  \n"); 
    fprintf(fp, "    }\n");    
    fprintf(fp, "\n"); 
    fprintf(fp, "    block ciphertext;  \n"); 
    fprintf(fp, "    srand(time(NULL)); \n"); 
    fprintf(fp, "    feistelCipher(plaintext, ciphertext);  \n"); 
    fprintf(fp, "    \n"); 
    fprintf(fp, "    FILE *file = fopen(\"plaintext&ciphertext.txt\", \"w\"); \n"); 
    fprintf(fp, "    if (file == NULL) {\n"); 
    fprintf(fp, "        printf(\"Could not open file£¡\\n\");\n"); 
    fprintf(fp, "        return 1;\n"); 
    fprintf(fp, "    }\n"); 
    fprintf(fp, "    fprintf(file, \"Plaintext: \");\n"); 
    fprintf(fp, "    for (i = 0; i < BLOCK_SIZE; i++) {\n"); 
    fprintf(fp, "        fprintf(file, \"%%02X \", plaintext[i]);\n"); 
    fprintf(fp, "    }\n");
    fprintf(fp, "    fprintf(file, \"\\nCiphertext: \");\n"); 
    fprintf(fp, "    for (i = 0; i < BLOCK_SIZE; i++) {\n"); 
    fprintf(fp, "        fprintf(file, \"%%02X \", ciphertext[i]);\n"); 
    fprintf(fp, "    }\n"); 
    fprintf(fp, "    fprintf(file, \"\\n\");\n"); 
    fprintf(fp, "    fclose(file); \n"); 
    fprintf(fp, "\n"); 
    fprintf(fp, "    return 0;\n");   
    fprintf(fp, "}\n");    
  
    fclose(fp);  
  
    char command[256];  
    snprintf(command, sizeof(command), "gcc -std=c99 Compiler_output.c -o Compiler_output.exe");  
    int status = system(command);  
    if (status != 0) {  
        perror("Failed to compile Compiler_output.c");  
        return 1;  
    }  
  
//    printf("Compiler_output has been successfully compiled.\n");  
    
    remove("Compiler_output.c"); 
    
    return 0; 
}
