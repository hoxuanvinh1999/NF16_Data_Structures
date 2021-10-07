test_binary_tree: main.o binary_tree.o 
	gcc -o test_binary_tree main.o binary_tree.o

main.o: main.c binary_tree.h
	gcc -c main.c

binary_tree.o: binary_tree.c binary_tree.h
	gcc -c binary_tree.c
					
clean:
	rm -f test_binary_tree *.o