// board header
// contains all the board functions

#include "chess_struct.h"

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

// initializes chess pieces
void startboard(char board[8][8]);

// prints board
void printboard(char board[8][8]);
    
// returns the number of points the color is ahead by
int getPoints(char board[8][8], char color);

// replay function 
void Replay(PLAYER *W, PLAYER *B, BMOVE *M, int turn, char color, char winner);

#endif // chess board