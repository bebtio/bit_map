
#include "bit_map.h"

#define BITS_IN_BYTE 8

struct bit_map_s
{
    unsigned char* map;

    // Number of bits user asked for.
    size_t num_bits;

    // Number of chars required to represent that amount of bits.
    size_t map_size;
};


typedef struct bit_map_index_s
{
    size_t map_index;
    size_t bit_index;

} bit_map_index;

// Returns a bit_map_index as a pair of size_t's.
bit_map_index get_bit_map_index( size_t bit_index );

// Checks that the requested bit_index doesn't exceed the bounds of a bit_map.
unsigned char check_bounds( bit_map bm, size_t bit_index );

// *********************************************************** //
// Will create a bit map that contains num_bits number of bits.
// *********************************************************** //
bit_map malloc_bit_map( size_t num_bits )
{
    // Allocate the bit map memory.
    bit_map bm = (bit_map)malloc(sizeof(struct bit_map_s));
    
    // Compute the number of chars needed to store num_bits number of bits.
    // This effectively rounds up to the nearest whole number of chars.
    size_t num_chars = (num_bits + BITS_IN_BYTE - 1) / BITS_IN_BYTE;

    // Allocate the number of chars needed to represent num_bits.
    bm->map      = (unsigned char*)malloc(sizeof(unsigned char) * num_chars);
    bm->num_bits = num_bits;
    bm->map_size = num_chars;

    // Make sure the bitmap is empty.
    clear_bit_map(bm);

    return(bm);
}

// *********************************************************** //
// Free bit_map memory.
// *********************************************************** //
void free_bit_map( bit_map bm )
{

    // Clear the data in the bit map.
    bm->map_size = 0;
    bm->num_bits = 0;
    clear_bit_map(bm);
    
    // Free the map memory.
    free(bm->map);
    bm->map = NULL;

    // Free the bit_map struct memory;
    free(bm);
    bm = NULL;
}

// *********************************************************** //
// Sets all bits to zero.
// *********************************************************** //
void clear_bit_map( bit_map bm )
{
    for( size_t i = 0; i < bm->map_size; i++ )
    {
        bm->map[i] &= 0;
    }
}

// *********************************************************** //
// Sets all bits to one.
// *********************************************************** //
void set_bit_map( bit_map bm )
{
    for( size_t i = 0; i < bm->map_size; i++ )
    {
        bm->map[i] |= 0xff;
    }
}

// *********************************************************** //
// Get the bit value at index bit_index.
// *********************************************************** //
unsigned char get_bit( bit_map bm, size_t bit_index )
{
    if( check_bounds(bm, bit_index) == OUT_OF_BOUNDS ) return(OUT_OF_BOUNDS);

    bit_map_index bmi = get_bit_map_index(bit_index);

    // Get the value of the bit at bit_index.
    unsigned char byte  = bm->map[bmi.map_index];
    unsigned char bit = ( byte >> bmi.bit_index) & 1;

    // Make sure we return 1 or 0.
    if( bit != 0)
    {
        return(1);
    }
    else
    {
        return(0);
    }
}

// *********************************************************** //
// Get the number of bits this bit map represents.
// *********************************************************** //
size_t get_num_bits( bit_map bm )
{
    return( bm->num_bits );
}

// *********************************************************** //
// Sets the bit at bit_index to 1.
// *********************************************************** //
unsigned char set_bit( bit_map bm, size_t bit_index)
{
    if( check_bounds(bm, bit_index) == OUT_OF_BOUNDS ) return(OUT_OF_BOUNDS);

    // Compute the map index and the bit index within that char.
    bit_map_index bmi = get_bit_map_index(bit_index);

    // Set that bit.
    bm->map[ bmi.map_index ] |=  (1 << bmi.bit_index);

    // Returns the value we just set.
    return(bm->map[ bmi.map_index ]);
}

// *********************************************************** //
// Sets the bit at bit_index to 0.
// *********************************************************** //
unsigned char clear_bit( bit_map bm, size_t bit_index)
{
    if( check_bounds(bm, bit_index) == OUT_OF_BOUNDS ) return(OUT_OF_BOUNDS);

    // Compute the map index and the bit index within that char.
    bit_map_index bmi = get_bit_map_index(bit_index);

    // And the bit with a 0.
    bm->map[ bmi.map_index ] &=  ~(1 << bmi.bit_index);

    // Returns the value we just set.
    return(bm->map[ bmi.map_index ]);
}

// *********************************************************** //
// Prints the contents of the bit_map.
// *********************************************************** //
void print_bits( bit_map bm )
{
    // Loop over each byte in the bit_map.
    for (size_t i = 0; i < bm->map_size; i++) 
    {
        // Loop over each bit in a this byte.
        for (int j = 7; j >= 0; j--)
        {
            // Use bitwise AND with a bitmask to extract each bit.
            int bit = (bm->map[i] >> j) & 1;
            printf("%d", bit);
        }

        printf(" ");
    }

    printf("\n");
}

// *********************************************************** //
// Creates a struct called bit_map_index that contains two elements
// map_index and bit_index. Since memory is only byte addressable
// this will help compute the value of a specific bit in memory.
// 
// map_index is the index of the byte array containing the bit at bit_index.
// bit_index is the index of the bit within that byte.
// *********************************************************** //
bit_map_index get_bit_map_index( size_t bit_index )
{
    bit_map_index bmidx = {0,0};

    // Get the index into the map array.
    bmidx.map_index = bit_index / BITS_IN_BYTE;
    
    // Get the index within that char.
    bmidx.bit_index = bit_index % BITS_IN_BYTE;

    return(bmidx);

}

unsigned char check_bounds( bit_map bm, size_t bit_index )
{
    if( bit_index > bm->num_bits )
    {
        printf("Error: bit_index of %zu is out of bounds\n", bit_index);
        printf("       Bit map size is: %zu.\n", bm->map_size);
        return(2);
    }

    return(0);
}
