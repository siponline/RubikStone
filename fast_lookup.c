#include <stdio.h>  
#include <stdlib.h>  
#include <stdint.h> 
#include "fast_lookup.h" 

/**  
 * Fast lookup function that retrieves data based on the filename, index, table size, and entry size.  
 *  
 * @param filename    Pointer to the filename which identifies the file containing the data.  
 * @param index       The index of the data to retrieve (starting from 0).  
 * @param table_size  The total number of entries in the data table. This value is used to ensure the index is within a valid range.  
 * @param entry_size  The byte size of each data entry. This value is used to calculate the offset when reading data from the file.  
 * @return            Returns a uint64_t value which is the data read from the specified index position in the file.  
 *                    If an error occurs (such as the file not existing, invalid index, etc.), it should return a value indicating an error.  
 *                    However, note that the actual implementation of this function needs to define how to handle error situations.  
 */
uint64_t fast_lookup(const char *filename, size_t index, size_t table_size, size_t entry_size);  
  
uint64_t fast_lookup(const char *filename, size_t index, size_t table_size, size_t entry_size) {  
    if (index >= table_size) {  
        fprintf(stderr, "Index out of range\n");  
        exit(EXIT_FAILURE);  
    }  
  
    FILE *file = fopen(filename, "rb");  
    if (file == NULL) {  
        perror("Failed to open file");  
        exit(EXIT_FAILURE);  
    }  
  
    //Calculate the offset of table items in the file
    off_t offset = index * entry_size;  
  
    //Move the file pointer to the correct location 
    if (fseek(file, offset, SEEK_SET) != 0) {  
        perror("Failed to seek in file");  
        fclose(file);  
        exit(EXIT_FAILURE);  
    }  
  
    //Read table entries  
    uint64_t entry;  
    if (fread(&entry, entry_size, 1, file) != 1) {  
        fprintf(stderr, "Failed to read entry from file\n");  
        fclose(file);  
        exit(EXIT_FAILURE);  
    }  
  
	//Close file
    fclose(file);  
  
    return entry;  
}
