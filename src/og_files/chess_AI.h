// AI header
// contains the minimax function for AI
#ifndef CHESS_AI_H
#define CHESS_AI_H

#include "chess_struct.h"

// minimax algorithm for the AI
int minimax(char board[8][8], char color, char incolor, int alpha, int beta, int depth, int minmaxer, PLAYER *W, PLAYER *B, BMOVE *M);

// puts the best bot move into the bot move structure, starts the minimax function
void bestbotmove(char board[8][8], char color, PLAYER *W, PLAYER *B, BMOVE *M);

// endgame points
int endgame(int x, int y, int i, int j, char board[8][8], char color,PLAYER *W, PLAYER *B);

#endif // chess AI