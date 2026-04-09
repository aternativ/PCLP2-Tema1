CC = gcc
CFLAGS = -Wall -Wextra -g

.PHONY: build clean

# Regula apelata de checker.sh
build: task1 task2 task3 task4

task1: task1.c
	$(CC) $(CFLAGS) task1.c -o task1

task2: task2.c
	$(CC) $(CFLAGS) task2.c -o task2

task3: task3.c
	$(CC) $(CFLAGS) task3.c -o task3

task4: task4.c
	$(CC) $(CFLAGS) task4.c -o task4

pack:
	zip Tanasi_Robert_315CD.zip task1.c task2.c task3.c task4.c

clean:
	rm -f task1 task2 task3 task4