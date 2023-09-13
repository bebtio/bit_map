#include "bit_map.h"


int main(int argc, char* argv[])
{
    bit_map bm = malloc_bit_map(8);

    set_bit(bm, 7);
    set_bit(bm,1);
    set_bit(bm,0);

    printf("After settings bits\n");
    printf("Bit 7 = %d\n", get_bit(bm,7));
    printf("Bit 1 = %d\n", get_bit(bm,1));
    printf("Bit 0 = %d\n", get_bit(bm,0));
    print_bits(bm);

    clear_bit(bm, 7);
    clear_bit(bm,1);
    clear_bit(bm,0);

    printf("After clearing bits\n");
    printf("Bit 7 = %d\n", get_bit(bm,7));
    printf("Bit 1 = %d\n", get_bit(bm,1));
    printf("Bit 0 = %d\n", get_bit(bm,0));
    print_bits(bm);

    printf("Num bits in map: %zu\n", get_num_bits(bm));

    int errorReturn = get_bit(bm,1000);
    printf("errorReturn = %d\n", errorReturn);
    clear_bit_map(bm);
    set_bit(bm,0);
    set_bit(bm,3);
    set_bit(bm,6);

    print_bits(bm);
    free_bit_map(bm);
    return(0);
}
