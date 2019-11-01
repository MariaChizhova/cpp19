OBJECTS=$(addprefix obj/, clist.o point_list.o main.o)

all: lab_05

obj:
	mkdir -p obj/
lab_05: $(OBJECTS)
	gcc -g -Wall -Wextra -Werror -fsanitize=address $(OBJECTS) -o lab_05
obj/clist.o: src/clist.c include/clist.h | obj
	gcc -g -c -Wall -Wextra -Werror -fsanitize=address -Iinclude src/clist.c -o obj/clist.o
obj/point_list.o: src/point_list.c include/point_list.h include/clist.h | obj
	gcc -g -c -Wall -Wextra -Werror -fsanitize=address -Iinclude src/point_list.c -o obj/point_list.o
obj/main.o: src/main.c include/point_list.h | obj
	gcc -g  -c -Wall -Wextra -Werror -fsanitize=address -Iinclude src/main.c -o obj/main.o
clean:
	rm -rf obj lab_05
