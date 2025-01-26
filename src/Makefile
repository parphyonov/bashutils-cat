CC=gcc
CFLAG=-c
STD_FLAGS=-Wall -Werror -Wextra -std=c11
VG_FLAGS=--tool=memcheck --leak-check=yes --track-origins=yes

all: main

main: clean s21_cat

s21_cat: s21_cat.o s21_cat_input.o s21_cat_logic.o s21_cat_output.o s21_cat_oset.o
	$(CC) $(STD_FLAGS) s21_cat.o s21_cat_input.o s21_cat_logic.o s21_cat_output.o s21_cat_oset.o -o s21_cat

s21_cat.o: s21_cat.c s21_cat_input.h s21_cat_logic.h s21_cat_output.h s21_cat_oset.h
	$(CC) $(CFLAG) $(STD_FLAGS) s21_cat.c -o s21_cat.o

s21_cat_input.o: s21_cat_input.c s21_cat_input.h s21_cat_oset.h
	$(CC) $(CFLAG) $(STD_FLAGS) s21_cat_input.c -o s21_cat_input.o

s21_cat_logic.o: s21_cat_logic.c s21_cat_logic.h
	$(CC) $(CFLAG) $(STD_FLAGS) s21_cat_logic.c -o s21_cat_logic.o

s21_cat_output.o: s21_cat_output.c s21_cat_output.h
	$(CC) $(CFLAG) $(STD_FLAGS) s21_cat_output.c -o s21_cat_output.o

s21_cat_oset.o: s21_cat_oset.c s21_cat_oset.h
	$(CC) $(CFLAG) $(STD_FLAGS) s21_cat_oset.c -o s21_cat_oset.o

clean:
	rm -rf *.o s21_cat

fc:
	clang-format -i *.c
	clang-format -i *.h

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem ./*.c

valgrind:
	valgrind $(VG_FLAGS) ./s21_cat ./lib/fellowship.txt

leaks:
	leaks --atExit -- ./s21_cat lib/fellowship.txt | grep -e "total"