CC=g++
CFLAGS=-I.
DEPS = bst.h
OBJ = test.cpp BinarySearchTree.cpp

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Coursework: $(OBJ)
	g++ -o $@ $^ $(CFLAGS)