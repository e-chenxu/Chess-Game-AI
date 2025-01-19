// ending checks header
// contains the functions that check for end contitions, in check blah blah

#ifndef CHESS_CHECKS_H
#define CHESS_CHECKS_H

#include "chess_struct.h"

// checks if the color's king is currently in check, then returns 1 if it is
int inCheck(char board[8][8], char color, PLAYER *W, PLAYER *B);

// returns 1 if a person is checkmated, 2 if stalemated
int winnercheck(char board[8][8], char color, PLAYER *W, PLAYER *B);

// checks for king check when castling
int kingpasscheck(char rightleft, char board[8][8], char color, PLAYER *W, PLAYER *B);

#endif // chess checks