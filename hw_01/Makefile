OBJECTS=$(addprefix obj/, main.o bmp.o)

all: hw_01

obj:
	mkdir -p obj/
hw_01: $(OBJECTS)
	gcc -g -Wall -Wextra -Werror -fsanitize=address $(OBJECTS) -o hw_01
obj/main.o: src/main.c include/bmp.h | obj
	gcc -g -c -Wall -Wextra -Werror -fsanitize=address -Iinclude src/main.c -o obj/main.o
obj/bmp.o: src/bmp.c include/bmp.h | obj
	gcc -g  -c -Wall -Wextra -Werror -fsanitize=address -Iinclude src/bmp.c -o obj/bmp.o
clean:
	rm -rf obj hw_01

