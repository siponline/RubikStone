// fast_lookup.h  
  
#ifndef FAST_LOOKUP_H  
#define FAST_LOOKUP_H  
  
#include <stdint.h>  
  
uint64_t fast_lookup(const char *filename, size_t index, size_t table_size, size_t entry_size);  
  
#endif // FAST_LOOKUP_H
