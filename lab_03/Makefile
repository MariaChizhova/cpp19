OBJECTS=$(addprefix obj/, clist.o main.o)

all: lab_03

obj:
	mkdir -p obj/
lab_03: $(OBJECTS)
	gcc -g -Wall -Wextra -Werror -fsanitize=address $(OBJECTS) -o lab_03
obj/clist.o: src/clist.c include/clist.h | obj
	gcc -g -c -Wall -Wextra -Werror -fsanitize=address -Iinclude src/clist.c -o obj/clist.o
obj/main.o: src/main.c include/clist.h | obj
	gcc -g  -c -Wall -Wextra -Werror -fsanitize=address -Iinclude src/main.c -o obj/main.o
clean:
	rm -rf obj lab_03
