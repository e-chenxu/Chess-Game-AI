// chess moves header
// contains the functions for player and AI move functions, and also the valid moves and moving to board functions

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include "chess_struct.h"

// edits the array of valid moves
int validmovesarray(int x, int y, int valid[27][2], char board[8][8], char curcolor, PLAYER *W, PLAYER *B, int on);

// returns 0 if input is false, then does main functions for the player input
int moveinput(char input[5], char board[8][8], char color, PLAYER *W, PLAYER *B);

// moves the piece to a place, checks for special moves
void movetoboard(int x, int y, int i, int j, char board[8][8], PLAYER *W, PLAYER *B, int tempcheck);

#endif // chess move