// chess checks functions

#include "chess_struct.h"
#include "chess_checks.h"
#include "chess_move.h"
#include <stdio.h>

// checks castling checks
int kingpasscheck(char rightleft, char board[8][8], char color, PLAYER *W, PLAYER *B){
    // returns if current color king is in check
    if (inCheck(board, color, W, B) == 1)
        return 0;
    // temporary board
    char tmpboard[8][8];
    int i,j;
    for (i = 0; i < 8; i++){
        for (j = 0; j < 8; j++){
            tmpboard[i][j] = board[i][j];
        }
    }
    // check to see if the spots are in check
    if (rightleft == 'R' && color == 'B'){
        for (i = 0; i < 2; i++){
            tmpboard[4 + i][7] = ' ';
            tmpboard[4 + i + 1][7] = 'k';
            if (inCheck(tmpboard, color, W, B) == 1)
                return 0;
        }
    }
    else if (rightleft == 'R' && color == 'W'){
        for (i = 0; i < 2; i++){
            tmpboard[4 + i][0] = ' ';
            tmpboard[4 + i + 1][0] = 'K';
            if (inCheck(tmpboard, color, W, B) == 1)
                return 0;
        }
    }
    else if (rightleft == 'L' && color == 'B'){
        for (i = 0; i < 2; i++){
            tmpboard[4 - i][7] = ' ';
            tmpboard[4 - i - 1][7] = 'k';
            if (inCheck(tmpboard, color, W, B) == 1)
                return 0;
        }
    }
    else if (rightleft == 'L' && color == 'W'){
        for (i = 0; i < 2; i++){
            tmpboard[4 - i][0] = ' ';
            tmpboard[4 - i - 1][0] = 'K';
            if (inCheck(tmpboard, color, W, B) == 1)
                return 0;
        }
    }
    return 1;    
}

// returns 1 if current color king is in check
int inCheck(char board[8][8], char color, PLAYER *W, PLAYER *B){
    int x,y,i,kingx,kingy;
    char lettera,letterz,letterzop,letteraop, colorop;
    int count = 0;
    int breakflag = 0;
    int valid[27][2];
    if (color == 'W'){
        letteraop = 'a';
        letterzop = 'z';
        lettera = 'A';
        letterz = 'Z';
        colorop = 'B';
    }
    else {
        letteraop = 'A';
        letterzop = 'Z';
        lettera = 'a';
        letterz = 'z';
        colorop = 'W';
    }
    // find the king's position
    for (x = 0; x < 8; x++){
        for (y = 0; y < 8; y++){
            if ((board[x][y] == 'K' || board[x][y] - 32 == 'K') && (board[x][y] >= lettera && board[x][y] <= letterz)){
                kingx = x;
                kingy = y;
                breakflag = 1;
                break;
            }
        }
        if (breakflag == 1)
            break;
    }
    // check all moves of every opponent piece and see if any of them contain the location of the king
    for (x = 0; x < 8; x++){
        for (y = 0; y < 8; y++){
            if (board[x][y] >= letteraop && board[x][y] <= letterzop){
                count = validmovesarray(x, y, valid, board, colorop, W, B,0);
                for (i = 0; i < count; i++){
                    if (valid[i][0] == kingx && valid[i][1] == kingy)
                        return 1;
                }
            }
        }
    }
    return 0;
}

// checcks for stalemate, check mate
int winnercheck(char board[8][8], char color, PLAYER *W, PLAYER *B){
    // temporary board
    char tmpboard[8][8];
    int valid[27][2];
    char lettera,letterz;
    int i,x,y,m,n;
    int count = 0;
    if (color == 'W'){
        lettera = 'A';
        letterz = 'Z';
    }
    else {
        lettera = 'a';
        letterz = 'z';
    }
    // check all moves of every own piece and see if all of them are in check
    for (x = 0; x < 8; x++){
        for (y = 0; y < 8; y++){
            if (board[x][y] >= lettera && board[x][y] <= letterz){
                count = validmovesarray(x, y, valid, board, color, W, B,0);
                for (i = 0; i < count; i++){
                    // reset the board (5 for loops)
                    for (m = 0; m < 8; m++){
                        for (n = 0; n < 8; n++){
                            tmpboard[m][n] = board[m][n];
                        }
                    }
                    // store temp info
                    StoreInfo(W,0);
                    StoreInfo(B,0);
                    movetoboard(x,y,valid[i][0],valid[i][1], tmpboard, W, B,1);
                    // get temp info
                    GetInfo(W,0);
                    GetInfo(B,0);
                    if (inCheck(tmpboard, color, W, B) == 0){
                        return 0;
                    }
                }
            }
        }
    }
    // returns 1 if checkmate, 2 if stalemate
    if (inCheck(board, color, W, B) == 1)
        return 1;
    else
        return 2;
}

// end of file