all: Huffman.c Huffman.h
	cc Huffman.c -o Huffman.exe
clean:
	rm a.out *.exe *.c~ 