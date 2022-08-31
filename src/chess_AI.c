// chess ai functions

#include "chess_struct.h"
#include "chess_board.h"
#include "chess_move.h"
#include "chess_checks.h"
#include "chess_AI.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// mini max alpha beta function, essentially this function recursively looks through a tree and returns the best move
int minimax(char board[8][8], char color, char incolor, int alpha, int beta, int depth, int minmaxer, PLAYER *W, PLAYER *B, BMOVE *M){
    // end of tree
    if (depth == 0)
        return getPoints(board,incolor);
    // variables
    char tmpboard[8][8];
    int valid[27][2];
    int count = 0;
    char lettera,letterz;
    int i,x,y,m,n,z,points;
    int maxpoints = -10000;
    int minpoints = 10000;
    if (color == 'W'){
        lettera = 'a';
        letterz = 'z';
        color = 'B';
    }
    else {
        lettera = 'A';
        letterz = 'Z';
        color = 'W';
    }
    // calculate middle rows first
    if (minmaxer == 1){
        y = 3;
        for (z = 0; z < 8; z++){
            y += (z % 2) ? z : -z;
            for (x = 0; x < 8; x++){
                if (board[x][y] >= lettera && board[x][y] <= letterz){
                    count = validmovesarray(x, y, valid, board, color, W, B,1);
                    for (i = 0; i < count; i++){
                        // reset the board (5 for loops )
                        for (m = 0; m < 8; m++){
                            for (n = 0; n < 8; n++){
                                tmpboard[m][n] = board[m][n];
                            }
                        }
                        // store temp info
                        StoreInfo(W,depth);
                        StoreInfo(B,depth);
                        StoreRInfo(M,depth);
                        
                        // if it can eat king, return big
                        if (board[valid[i][0]][valid[i][1]] == 'K' || board[valid[i][0]][valid[i][1]] - 32 == 'K'){
                            GetInfo(W,depth);
                            GetInfo(B,depth);
                            GetRInfo(M,depth);
                            return 2000;
                        }
                        
                        // no repeat too much
                        if (GetPiece(M) == board[x][y]){
                            SetRepeat(M,GetRepeat(M) + 1);
                            if (GetRepeat(M) >= 7){
                                GetInfo(W,depth);
                                GetInfo(B,depth);
                                GetRInfo(M,depth);
                                return -250;
                            }
                        }
                        
                        movetoboard(x,y,valid[i][0],valid[i][1], tmpboard, W, B, 1);
                        points = minimax(tmpboard,color,incolor,alpha,beta,depth - 1,0,W,B,M);
                        
                        if (points > maxpoints)
                            maxpoints = points;
                        // get temp info
                        GetInfo(W,depth);
                        GetInfo(B,depth);
                        GetRInfo(M,depth);
                        // alpha prune
                        if (points > alpha)
                            alpha = points;
                        if (beta <= alpha)
                            return maxpoints;
                    }
                }
            }
        }
        return maxpoints;
    }
    else {
        y = 3;
        for (z = 0; z < 8; z++){
            y += (z % 2) ? z : -z;
            for (x = 0; x < 8; x++){
                if (board[x][y] >= lettera && board[x][y] <= letterz){
                    count = validmovesarray(x, y, valid, board, color, W, B,1);
                    for (i = 0; i < count; i++){
                        // reset the board (5 for loops )
                        for (m = 0; m < 8; m++){
                            for (n = 0; n < 8; n++){
                                tmpboard[m][n] = board[m][n];
                            }
                        }
                        // store temp info
                        StoreInfo(W,depth);
                        StoreInfo(B,depth);
                        
                        // return if eat king
                        if (board[valid[i][0]][valid[i][1]] == 'K' || board[valid[i][0]][valid[i][1]] - 32 == 'K'){
                            GetInfo(W,depth);
                            GetInfo(B,depth);
                            return -2000;
                        }
                        
                        movetoboard(x,y,valid[i][0],valid[i][1], tmpboard, W, B, 1);
                        points = minimax(tmpboard,color,incolor,alpha,beta,depth - 1,1,W,B,M);
                        if (points < minpoints)
                            minpoints = points;
                        // get temp info
                        GetInfo(W,depth);
                        GetInfo(B,depth);
                        // beta prune
                        if (points < beta)
                            beta = points;
                        if (beta <= alpha){
                            return minpoints;
                        }
                    }
                }
            }
        }
        // more points if checkmate
        if (minpoints >= 1700 && inCheck(board, color, W, B) == 1)
            return 3000;
        return minpoints;
    }
    
}

// endgame stuff
int endgame(int x, int y, int i, int j, char board[8][8], char color, PLAYER *W, PLAYER *B){
    int kingx,kingy,m,n,z,o,p;
    char letterzop,letteraop,colorop;
    int eatflag = 0;
    int breakflag = 0;
    int count = 0;
    int pointcount = 0;
    int valid[27][2];
    char tmpboard[8][8];
    if (color == 'W'){
        letteraop = 'a';
        letterzop = 'z';
        colorop = 'B';
    }
    else{
        letteraop = 'A';
        letterzop = 'Z';
        colorop = 'W';
    }
    // find enemy king position
    for (m = 0; m < 8; m++){
        for (n = 0; n < 8; n++){
            if ((board[m][n] == 'K' || board[m][n] - 32 == 'K') && (board[m][n] >= letteraop && board[m][n] <= letterzop)){
                kingx = m;
                kingy = n;
                breakflag = 1;
                break;
            }
        }
        if (breakflag == 1)
            break;
    }
    // bonus pointns for putting enemy king in check, none if king is edge
    if (inCheck(board, colorop, W, B) == 1){
        pointcount+=7;
        if (kingx == 0 || kingx == 7 || kingy == 0 || kingy == 7)
            pointcount-=7;
    }
    // bonus points for moving a pawn if its safe
    if (board[i][j] == 'P' || board[i][j] - 32 == 'P'){
        pointcount+=20;
        return pointcount;
    }
    // add how many spaces that the king is coverd
   for (m = 0; m < 8; m++){
        for (n = 0; n < 8; n++){
            if (board[m][n] >= letteraop && board[m][n] <= letterzop){
                count = validmovesarray(m, n, valid, board, colorop, W, B,1);
                for (z = 0; z < count; z++){
                    // reset the board (5 for loops )
                    for (o = 0; o < 8; o++){
                        for (p = 0; p < 8; p++){
                            tmpboard[o][p] = board[o][p];
                        }
                    }
                    // store temp info
                    StoreInfo(W,15);
                    StoreInfo(B,15);
                    // if its a spot where u can get eaten, minus
                    if (valid[z][0] == i && valid[z][1] == j)
                        eatflag = 1;
                    else
                        eatflag = 0;
                    movetoboard(m,n,valid[z][0],valid[z][1], tmpboard, W, B, 1);
                    // this will try to get the pieces near the king
                    if (board[m][n] == 'K' || board[m][n] - 32 == 'K'){
                        if (inCheck(tmpboard, colorop, W, B) == 1){
                            pointcount+=2;
                            if (kingx == 0 || kingx == 7 || kingy == 0 || kingy == 7)
                                pointcount+=2;
                            // check corner push to left side of king
                            if (kingx < 1 && valid[z][0] > kingx){
                                pointcount+=3;
                            }
                            else if (kingx < 2 && valid[z][0] > kingx)
                                pointcount+=2;
                            //  to right 
                            else if (kingx < 4 && valid[z][0] > kingx)
                                pointcount++;
                            if (kingx > 6 && valid[z][0] < kingx){
                                pointcount+=3;
                            }
                            else if (kingx > 5 && valid[z][0] < kingx)
                                pointcount+=2;
                            else if (kingx > 3 && valid[z][0] < kingx)
                                pointcount++;
                            //up 
                            if (kingy > 6 && valid[z][1] < kingy){
                                pointcount+=3;
                            }
                            else if (kingy > 5 && valid[z][1] < kingy)
                                pointcount+=2;
                            else if (kingy > 3 && valid[z][1] < kingy)
                                pointcount++;
                            // down
                            if (kingy < 1 && valid[z][1] > kingy){
                                pointcount+=3;
                            }
                            else if (kingy < 2 && valid[z][1] > kingy)
                                pointcount+=2;
                            else if (kingy < 4 && valid[z][1] > kingy)
                                pointcount++;
                        }
                    }
                    else if (inCheck(tmpboard, colorop, W, B) == 0){
                        //printf("brh%c%d .%d.%d.%d.%d",board[m][n],count,m,n,valid[z][0],valid[z][1]);
                        pointcount-=3;
                        // if promote pawn minus
                        if ((board[m][n] == 'P' || board[m][n] - 32 == 'P') && (n == 1 || n == 6))
                            pointcount-=30;
                        if (eatflag == 1)
                            pointcount-=25;
                    }
                    GetInfo(W,15);
                    GetInfo(B,15);
                }
            }
        }
    }
    // bonus if covered spaces is far from edge
    // bonus points for moving king towards enemy king
    // find the enemy king's position
    // cut of as many spaces as posibble
    // move king towards enemy king
    if (board[i][j] == 'K' || board[i][j] - 32 == 'K'){
            // check x close
            if (abs(kingx - i) < abs(kingx - x))
                pointcount+=5;
            else if (abs(kingx - i) != abs(kingx - x))
                pointcount--;
            if (abs(kingy - j) < abs(kingy - y))
                pointcount+=5;
            else if (abs(kingy - j) != abs(kingy - y))
                pointcount--;
    }
    if (abs(kingx - i) < abs(kingx - x))
        pointcount++;
    else
        pointcount--;
    if (abs(kingy - j) < abs(kingy - y))
        pointcount++;
    else
        pointcount--;
    return pointcount;
}

// AI that sets the best move
void bestbotmove(char board[8][8], char color, PLAYER *W, PLAYER *B, BMOVE *M){
    int points;
    // temporary board
    char tmpboard[8][8];
    int valid[27][2];
    int count = 0;
    int piececount = 0;
    int random = 0;
    char lettera,letterz,colorop;
    int i,x,y,m,n,z;
    int endflag = 0;
    if (color == 'W'){
        lettera = 'A';
        letterz = 'Z';
        colorop = 'B';
    }
    else {
        lettera = 'a';
        letterz = 'z';
        colorop = 'W';
    }
    // check for endgame, add bonus points for certain scenarios
    for (m = 0; m < 8; m++){
        for (n = 0; n < 8; n++){
            if (board[m][n] != ' ')
                piececount++;
        }
    }
    // boost ai when low
    if (piececount < 5 && getPoints(board,color) > -128){
        SetAI(M,8);
        endflag = 1;
    }
    else if (piececount < 7 && getPoints(board,color) > -128){
        SetAI(M,7);
        endflag = 1;
    }
    // set random move pick
    random = piececount/4 + 2;
    // start minimax function
    srand(time(0));
    int max = -10000;
    y = 3;
    for (z = 0; z < 8; z++){
        y += (z % 2) ? z : -z;
        for (x = 0; x < 8; x++){
            if (board[x][y] >= lettera && board[x][y] <= letterz){
                count = validmovesarray(x, y, valid, board, color, W, B,1);
                for (i = 0; i < count; i++){
                    // reset the board (5 for loops )
                    for (m = 0; m < 8; m++){
                        for (n = 0; n < 8; n++){
                            tmpboard[m][n] = board[m][n];
                        }
                    }
                    // store temp info
                    StoreInfo(W,16);
                    StoreInfo(B,16);
                    StoreRInfo(M,16);
                    movetoboard(x,y,valid[i][0],valid[i][1], tmpboard, W, B, 1);
                    
                    // point stuff
                    // make sure doesnt go to a spot where it gets checked
                    if (inCheck(tmpboard, color, W, B) == 1)
                        continue;
                    if (winnercheck(tmpboard, colorop, W, B) == 1)
                        points+=200;
                    points = minimax(tmpboard,color,color,-10000,10000,GetAI(M),0,W,B,M);
                    // no repeat
                    if ((GetPiece(M) == board[x][y]) && GetRepeat(M) > GetAI(M))
                        points = -200;
                    // add points at end
                    if (endflag == 1)
                        points += endgame(x,y,valid[i][0],valid[i][1], tmpboard, color,W,B);
                    // prioritize at center
                    if (valid[i][0] > 2 && valid[i][0] < 5 && valid[i][1] > 2 && valid[i][1] < 5)
                        points+=2;
                    else if (valid[i][0] > 1 && valid[i][0] < 6 && valid[i][1] > 1 && valid[i][1] < 6)
                        points++;
                        
                    if (points > max){
                        SetX(M,x);
                        SetY(M,y);
                        SetI(M,valid[i][0]);
                        SetJ(M,valid[i][1]);
                        max = points;
                    }
                    else if (points == max){
                        if (rand() % random == 1){
                            SetX(M,x);
                            SetY(M,y);
                            SetI(M,valid[i][0]);
                            SetJ(M,valid[i][1]);
                        }
                    }
                    // get temp info
                    GetInfo(W,16);
                    GetInfo(B,16);
                    GetRInfo(M,16);
                }
            }
        }
    }
    movetoboard(GetX(M),GetY(M),GetI(M),GetJ(M),board, W, B, 1);
    // make sure no repeat same move over nd over
    if (GetPiece(M) == board[GetI(M)][GetJ(M)]){
        SetRepeat(M,GetRepeat(M) + 1);
    }
    else {
        SetRepeat(M,0);
    }
    SetPiece(M,board[GetI(M)][GetJ(M)]);
}

// end of file
