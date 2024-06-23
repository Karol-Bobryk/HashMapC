make:
	gcc *.c -o ./bin/main -lm; valgrind ./bin/main 
