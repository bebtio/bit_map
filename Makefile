

bit_map: main.c bit_map.c
	gcc main.o -g bit_map.o -Iinclude -o bit_map

main.c:
	gcc -c -g src/main.c -o main.o -Iinclude

bit_map.c:
	gcc -c -g src/bit_map.c -o bit_map.o -Iinclude

.PHONY: clean

clean:
	rm *.o bit_map1
