CC=gcc
C_FLAG=-c
STD_FLAGS=-Wall -Werror -Wextra -std=c11
VG_FLAGS=--tool=memcheck --leak-check=yes --track-origins=yes

all: main

main: clean fc cpp compile_cat_tests vg_basic

compile_cat_tests: cat_tests.o common.o
	$(CC) $(STD_FLAGS) cat_tests.o common.o -o cat_tests

run_cat_tests:
	./cat_tests

cat_tests.o: cat_tests.c ../common/common.h ../grep/s21_grep_helpers.h
	$(CC) $(C_FLAG)  $(STD_FLAGS) cat_tests.c -o cat_tests.o

common.o: ../common/common.c ../common/common.h
	$(CC) $(C_FLAG) $(STD_FLAGS) ../common/common.c -o common.o

clean:
	rm -rf *.o

fc:
	clang-format -i *.c

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem ./*.c

vg_basic:
	valgrind $(VG_FLAGS) ./cat_tests