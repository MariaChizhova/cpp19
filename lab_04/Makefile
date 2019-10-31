OBJECTS=$(addprefix obj/, mergesort.o main.o my_memcpy.o)

all: lab_04

obj:
	mkdir -p obj/
lab_04: $(OBJECTS)
	gcc -g -Wall -Wextra -Werror -fsanitize=address $(OBJECTS) -o lab_04
obj/mergesort.o: src/mergesort.c include/mergesort.h include/my_memcpy.h | obj
	gcc -g -c -Wall -Wextra -Werror -fsanitize=address -Iinclude src/mergesort.c -o obj/mergesort.o
obj/main.o: src/main.c include/mergesort.h include/my_memcpy.h | obj
	gcc -g  -c -Wall -Wextra -Werror -fsanitize=address -Iinclude src/main.c -o obj/main.o
obj/my_memcpy.o: src/my_memcpy.c include/my_memcpy.h | obj
	gcc -g  -c -Wall -Wextra -Werror -fsanitize=address -Iinclude src/my_memcpy.c -o obj/my_memcpy.o
clean:
	rm -rf obj lab_04

