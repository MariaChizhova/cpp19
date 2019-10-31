LISTOBJECTS=$(addprefix obj/, str.o test.o test_str.o)

all: lab_02

obj:
	mkdir -p obj/
lab_02: $(LISTOBJECTS)
	gcc -Wall -Wextra -Werror -fsanitize=address $(LISTOBJECTS) -o lab_02
obj/str.o: src/str.c include/str.h | obj
	gcc -c -Wall -Wextra -Werror -fsanitize=address -Iinclude src/str.c -o obj/str.o
obj/test.o: src/test.c include/test_str.h | obj
	gcc -c -Wall -Wextra -Werror -Iinclude -fsanitize=address  src/test.c -o obj/test.o
obj/test_str.o: src/test_str.c include/test_str.h include/str.h | obj
	gcc -c -Wall -Wextra -Werror -fsanitize=address -Iinclude src/test_str.c -o obj/test_str.o
clean:
	rm -rf obj lab_02
