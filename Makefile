# Makefile: Makefile for Chess_vs_AI
# EECS 22L SPRING 2021
# Team 24 

# variables
CC     = gcc
CFLAGS = -ansi -std=c99 -Wall -c
LFLAGS = -ansi -std=c99 -Wall
OBJECTS = $(addprefix bin/, chess_main.o chess_move.o chess_struct.o chess_board.o chess_AI.o chess_checks.o)

all: bin/Chess_vs_AI

clean:
	rm -f bin/*.o bin/Chess_vs_AI

tar:
	tar -czvf ../Chess_Alpha_src.tar.gz Chess_Alpha_src

########### generate object files ###########

#target to generate chess_struct.o
bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

########### generate executables ###########

#target to generate Chess_vs_AI
bin/Chess_vs_AI: $(OBJECTS)
	$(CC) $(LFLAGS) $^ -o $@

#end of file
