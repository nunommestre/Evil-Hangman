CC = gcc
CFLAGS = -Wall --std=c99 -g
OBJECTS = main.o string.o generic.o AVL_Tree.o
TESTOBJ = string.o unit_test.o test_def.o
ALL: play_hangman unit_test
play_hangman: $(OBJECTS)
	$(CC) $(CFLAGS) -o play_hangman $(OBJECTS)
main.o: main.c 
	$(CC) $(CFLAGS) -c main.c -o main.o
string.o: my_string.c
	$(CC) $(CFLAGS) -c my_string.c -o string.o
unit_test: $(TESTOBJ)
	$(CC) $(CFLAGS) -o unit_test $(TESTOBJ)
unit_test.o: unit_test.c
	$(CC) $(CFLAGS) -c unit_test.c -o unit_test.o
test_def.o: test_def.c
	$(CC) $(CFLAGS) -c test_def.c -o test_def.o
generic.o: generic_vector.c
	$(CC) $(CFLAGS) -c generic_vector.c -o generic.o
AVL_Tree.o: AVL_Tree.c
	$(CC) $(CFLAGS) -c AVL_Tree.c -o AVL_Tree.o
clean:
	rm play_hangman $(OBJECTS) unit_test unit_test.o test_def.o
