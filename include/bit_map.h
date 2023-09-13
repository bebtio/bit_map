
#ifndef __BIT_MAP_H__
#define __BIT_MAP_H__

#include <stdio.h>
#include <stdlib.h>

typedef enum 
{
    OUT_OF_BOUNDS = 2,
} BIT_MAP_ERROR;

typedef struct bit_map_s* bit_map;


// *********************************************************** //
// Will create a bit map that contains num_bits number of bits.
// *********************************************************** //
bit_map malloc_bit_map( size_t num_bits );

// *********************************************************** //
// Free the bit_map memory.
// *********************************************************** //
void free_bit_map( bit_map bm );

// *********************************************************** //
// Sets all bits to zero.
// *********************************************************** //
void clear_bit_map( bit_map bm );

// *********************************************************** //
// Get the bit value at index bit_index.
// *********************************************************** //
unsigned char get_bit( bit_map bm, size_t bit_index );

// *********************************************************** //
// Get the number of bits this bit map represents.
// *********************************************************** //
size_t get_num_bits( bit_map bm );

// *********************************************************** //
// Sets the bit at bit_index to 1.
// *********************************************************** //
unsigned char set_bit( bit_map bm, size_t bit_index);

// *********************************************************** //
// Sets the bit at bit_index to 0.
// *********************************************************** //
unsigned char clear_bit( bit_map bm, size_t bit_index);

// *********************************************************** //
// Prints the contents of the bit_map.
// *********************************************************** //
void print_bits( bit_map bm );

#endif
