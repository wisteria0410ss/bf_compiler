test.out: test.c $(filter-out ../obj/main.o,$(wildcard ../obj/*.o))
	gcc -O2 -Wall -Wextra $^ -o $@

run: test.out
	./$<