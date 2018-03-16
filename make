CC = gcc

all: main.o board.o
  $(CC) main.o board.o -o gameoflife

main: main.c
  $(CC) main.c -c -o main.o

board.o: board.c board.h
  $(CC) board.c -c -o board.o