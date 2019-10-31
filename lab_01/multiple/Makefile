LISTOBJECTS=$(addprefix bin/, main.o algorithm.o io.o util.o)

all: lab1

bin:
	mkdir -p bin/
lab1: $(LISTOBJECTS)
	gcc -Wall -Wextra -Werror $(LISTOBJECTS) -o lab1
bin/main.o: src/main.c include/io.h include/algorithm.h include/util.h | bin
	gcc -c -Wall -Wextra -Werror -Iinclude src/main.c -o bin/main.o
bin/io.o: src/io.c include/io.h | bin
	gcc -c -Wall -Wextra -Werror -Iinclude src/io.c -o bin/io.o
bin/util.o: src/util.c include/util.h include/io.h | bin
	gcc -c src/util.c -o bin/util.o -Wall -Wextra -Werror -Iinclude
bin/algorithm.o: src/algorithm.c include/algorithm.h include/io.h include/util.h | bin
	gcc -c -Wall -Wextra -Werror -Iinclude src/algorithm.c -o bin/algorithm.o
clean:
	rm -rf bin lab1
