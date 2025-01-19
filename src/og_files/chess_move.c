// chess move functions

#include "chess_struct.h"
#include "chess_move.h"
#include "chess_checks.h"
#include <stdio.h>

// move input for human input
int moveinput(char input[5], char board[8][8], char color, PLAYER *W, PLAYER *B){
    // 0 exit condition
    if (input[0] == '0')
        return 2;
    // array of valid moves 
    int valid[27][2];
    char temparray[8][8];
    int count;
    // first check to see if the player picked the right piece
    int x = input[0] - 'a';
    int y = input[1] - '1'; 
    int i = input[2] - 'a';
    int j = input[3] - '1';
    // check if out of bounds
    if (x < 0 || x > 7 || y < 0 || y > 7 || i < 0 || i > 7 || j < 0 || j > 7){
        printf("Invalid Move! Pick one of your pieces!\n");
        return 0;
    }
    // checking letters match with color
    // white = uppercase, black = lowercase
    if (color == 'W'){
        if (board[x][y] < 'A' || board[x][y] > 'Z'){
            printf("Invalid Move! Pick one of your pieces!\n");
            return 0;
        }
    }
    else if (color == 'B'){
        if (board[x][y] < 'a' || board[x][y] > 'z'){
            printf("Invalid Move! Pick one of your pieces!\n");
            return 0;
        }
    }
    count = validmovesarray(x,y,valid,board,color,W,B,1);
    // check if the move is in the valid moves array
    // make a temp array and check if the move input will not be checkmated
    for (int m = 0; m < 8; m++){
        for (int n = 0; n < 8; n++){
            temparray[m][n] = board[m][n];
        }
    }
    for (int k = 0; k < count; k++){
        if (valid[k][0] == i && valid[k][1] == j){
            // temporary variables that store the data of white, black
            // store temp info
            StoreInfo(W,0);
            StoreInfo(B,0);
            movetoboard(x,y,i,j,temparray,W,B,1);
            if (inCheck(temparray, color, W, B) == 1){
                printf("Wrong Move! You will be checkmated!\n");
                return 0;
            }
            // get temp info
            GetInfo(W,0);
            GetInfo(B,0);
            movetoboard(x,y,i,j,board, W, B,0);
            return 1;
        }
    }
    printf("Invalid move! Try again!\n");
    return 0;
} 

// moves the input to the board, does special moves also
void movetoboard(int x, int y, int i, int j, char board[8][8], PLAYER *W, PLAYER *B, int tempcheck){
    char option;
    // temp check will print messages and ask for pawn, else it will default queen
    // checking for pawn promotion
    //setting an en passant
    // checking if a pawn moved twice, sets the x value of where you can passant, also check if the move is a passant
    if (board[x][y] == 'P'){
        // check if a white pawn is doing a passant
        if (board[i][j] == ' ' && (x - i == 1 || x - i == -1)){
            board[i][j-1] = ' ';
            if (tempcheck == 0)
                printf("EN PASSANT!!!\n");
        }
        // check if white pawn moved up twice, then set passant
        else if (j - y == 2){
            SetPassant(W, i);
            SetPassant(B, 10);
            board[i][j] = board[x][y];
            board[x][y] = ' ';
            return;
        }
        // white pawn promotion
        else if (j == 7){
            // default queen
            if (tempcheck == 1){
                board[x][y] = ' ';
                board[i][j] = 'Q';
                return;
            }
            printf("PROMOTE PAWN!!! What would you like to promote to?\nQ - Queen\nN - Knight\nR - Rook\nB - Bishop\nType the respective character: ");
            scanf(" %c", &option);
            board[x][y] = ' ';
            switch (option){
                case 'Q':
                    board[i][j] = 'Q';
                    printf("Promoting to Queen...\n");
                    return;
                case 'N':
                    board[i][j] = 'N';
                    printf("Promoting to Knight...\n");
                    return;
                case 'R':
                    board[i][j] = 'R';
                    printf("Promoting to Rook... (why not just pick queen?)\n");
                    return;
                case 'B':
                    board[i][j] = 'B';
                    printf("Promoting to Bishop... (why not just pick queen?)\n");
                    return;
                default:
                    board[i][j] = 'Q';
                    printf("Couldn't read input. Defaulting to Queen...\n");
                    return;
            }
        }
    }
    else if (board[x][y] == 'p'){
        // check if a black pawn is doing a passant
        if (board[i][j] == ' ' && (x - i == 1 || x - i == -1)){
            board[i][j+1] = ' ';
            if (tempcheck == 0)
                printf("EN PASSANT!!!\n");
        }
        // check if black pawn moved down twice, then set passant
        else if (y - j == 2){
            SetPassant(B, i);
            SetPassant(W, 10);
            board[i][j] = board[x][y];
            board[x][y] = ' ';
            return;
        }
        // black pawn promotion
        else if (j == 0){
           // default queen
            if (tempcheck == 1){
                board[x][y] = ' ';
                board[i][j] = 'q';
                return;
            }
            printf("PROMOTE PAWN!!! What would you like to promote to?\nQ - Queen\nN - Knight\nR - Rook\nB - Bishop\nType the respective character: ");
            scanf(" %c", &option);
            board[x][y] = ' ';
            switch (option){
                case 'Q':
                    board[i][j] = 'Q';
                    printf("Promoting to Queen...\n");
                    return;
                case 'N':
                    board[i][j] = 'N';
                    printf("Promoting to Knight...\n");
                    return;
                case 'R':
                    board[i][j] = 'R';
                    printf("Promoting to Rook... (why not just pick queen?)\n");
                    return;
                case 'B':
                    board[i][j] = 'B';
                    printf("Promoting to Bishop... (why not just pick queen?)\n");
                    return;
                default:
                    board[i][j] = 'Q';
                    printf("Couldn't read input. Defaulting to Queen...\n");
                    return;
            }
        }
    }
    // chek for castling, move rook to behind
    // check if king,rook has moved based on if the player selected their position
    // also checks if enemy ate it
    if ((x == 4 && y == 0) || (i == 4 && j == 0))
        SetKing(W);
    else if ((x == 4 && y == 7) || (i == 4 && j == 0))
        SetKing(B);
    else if ((x == 0 && y == 0) || (i == 0 && j == 0))
        SetLRook(W);
    else if ((x == 0 && y == 7) || (i == 0 && j == 7))
        SetLRook(B);
    else if ((x == 7 && y == 0) || (i == 7 && j == 0))
        SetRRook(W);
    else if ((x == 7 && y == 7) || (i == 7 && j == 7))
        SetRRook(B);
        
    // right side black
    if (board[x][y] == 'k' && (i - x == 2)){
        board[7][7] = ' ';
        board[5][7] = 'r';
        SetRRook(B);
        if (tempcheck == 0)
            printf("CASTLING!!!\n");
    }
    // left side black
    else if (board[x][y] == 'k' && (x - i == 2)){
        board[0][7] = ' ';
        board[3][7] = 'r';
        SetLRook(B);
        if (tempcheck == 0)
            printf("CASTLING!!!\n");
    }
    // right side white
    else if (board[x][y] == 'K' && (i - x == 2)){
        board[7][0] = ' ';
        board[5][0] = 'R';
        SetRRook(W);
        if (tempcheck == 0)
            printf("CASTLING!!!\n");
    }
    // left side white
    else if (board[x][y] == 'K' && (x - i == 2)){
        board[0][0] = ' ';
        board[3][0] = 'R';
        SetLRook(W);
        if (tempcheck == 0)
            printf("CASTLING!!!\n"); 
    }
    
    // moves the piece
    board[i][j] = board[x][y];
    board[x][y] = ' ';
    SetPassant(W, 10);
    SetPassant(B, 10);
}

// gets an array of valid moves and puts moves in it
// return the count to here
int validmovesarray(int x, int y, int valid[27][2], char board[8][8], char curcolor, PLAYER *W, PLAYER *B, int on){
    // count position in array
    int count = 0;
    int range, tmprange;
    int i,j;
    char letteraop, letterzop, lettera, letterz; 
    // sets oppoonent floor and ceiling so we know which color the current can eat, also their own
    if (curcolor == 'W'){
        letteraop = 'a';
        letterzop = 'z';
        lettera = 'A';
        letterz = 'Z';
    }
    else{
        letteraop = 'A';
        letterzop = 'Z';
        lettera = 'a';
        letterz = 'z';
    }
    // pawn (different based on color, black goes down, white goes up)
    if (board[x][y] == 'P' || board[x][y] - 32 == 'P'){
        if (curcolor == 'W')
            range = 1;
        else
            range = -1;
        // check if can attack
        // check if not on right border,top,bot first, so can attack up/down and right
        if (x != 7 && y != 0 && y != 7){
            if (board[x+1][y+range] >= letteraop && board[x+1][y+range] <= letterzop){
                valid[count][0] = x+1;
                valid[count][1] = y+range;
                count++;
            }
        } 
        // check if not on left border,top,bot first, so can attack up/down and left
        if (x != 0 && y != 0 && y != 7){
            if (board[x-1][y+range] >= letteraop && board[x-1][y+range] <= letterzop){
                valid[count][0] = x-1;
                valid[count][1] = y+range;
                count++;
            }
        }
        // CHECK FOR PASSANT HERE vvvvvvvvvv
        // passant check for white
        if (board[x][y] == 'P' && y == 4 && (GetPassantX(B) - x == 1 || GetPassantX(B) - x == -1)){
            valid[count][0] = GetPassantX(B);
            valid[count][1] = y+1;
            count++;
        }
        // passant check for black
        else if (board[x][y] == 'p' && y == 3 && (GetPassantX(W) - x == 1 || GetPassantX(W) - x == -1)){
            valid[count][0] = GetPassantX(W);
            valid[count][1] = y-1;
            count++;
        }
        
        // check if it is in a position to move twice
        if ((y == 1 && curcolor == 'W') || (y == 6 && curcolor == 'B'))
            range = 2;
        else
            range = 1;
        // check empty spaces
        for (i = 1; i <= range; i++){
            if (curcolor == 'W')
                tmprange = y + i;
            else
                tmprange = y - i;
            if (tmprange < 0 || tmprange > 7)
                break;
            if (board[x][tmprange] == ' '){
                valid[count][0] = x;
                valid[count][1] = tmprange;
                count++;
            }
            else 
                break;
        }
        return count;
    }
    // horse
    // you can do this with an array of moves also i think
    if (board[x][y] == 'N' || board[x][y] - 32 == 'N'){
        for (i = -2; i <= 4; i += 4){
            for (j = -1; j <= 1; j += 2){
                range = x + i;
                tmprange = y + j;
                // super long check to see if its not out of bounds and is not their own pawn
                if ((range >= 0 && range <= 7 && tmprange >= 0 && tmprange <= 7) && (board[range][tmprange] < lettera || board[range][tmprange] > letterz)){
                    valid[count][0] = range;
                    valid[count][1] = tmprange;
                    count++;
                }
                range = x + j;
                tmprange = y + i;
                // checks the other half of avaliable sapces
                if ((range >= 0 && range <= 7 && tmprange >= 0 && tmprange <= 7) && (board[range][tmprange] < lettera || board[range][tmprange] > letterz)){
                    valid[count][0] = range;
                    valid[count][1] = tmprange;
                    count++;
                }
            }
        }
        return count;
    }
    // check up / down , left / right straight for king,queen,rook, no bishop
    int tmpx, tmpy;
    int kingbreak = 0;
    if (board[x][y] == 'K' || board[x][y] - 32 == 'K')
        kingbreak = 1;
    if (board[x][y] != 'B' && board[x][y] - 32 != 'B'){
        // up
        for (i = 1; i < 8 - y; i++){
            // cehck if blank
            tmpy = y+i;
            if (board[x][tmpy] == ' '){
                valid[count][0] = x;
                valid[count][1] = tmpy;
                count++;
            }
            // if its a oppoonent, then u put the thing in array and break
            else if (board[x][tmpy] >= letteraop && board[x][tmpy] <= letterzop){
                valid[count][0] = x;
                valid[count][1] = tmpy;
                count++;
                break;
            }
            // if its ur own piece u break
            else if (board[x][tmpy] >= lettera && board[x][tmpy] <= letterz)
                break;
            // if king, break after 1
            if (kingbreak == 1)
                break;
        }
        // down
        for (i = 1; i <= y; i++){
            // cehck if blank
            tmpy = y-i;
            if (board[x][tmpy] == ' '){
                valid[count][0] = x;
                valid[count][1] = tmpy;
                count++;
            }
            // if its a oppoonent, then u put the thing in array and break
            else if (board[x][tmpy] >= letteraop && board[x][tmpy] <= letterzop){
                valid[count][0] = x;
                valid[count][1] = tmpy;
                count++;
                break;
            }
            // if its ur own piece u break
            else if (board[x][tmpy] >= lettera && board[x][tmpy] <= letterz)
                break;
            // if king, break after 1
            if (kingbreak == 1)
                break;
        }
        // left
        for (i = 1; i <= x; i++){
            // cehck if blank
            tmpx = x-i;
            if (board[tmpx][y] == ' '){
                valid[count][0] = tmpx;
                valid[count][1] = y;
                count++;
            }
            // if its a oppoonent, then u put the thing in array and break
            else if (board[tmpx][y] >= letteraop && board[tmpx][y] <= letterzop){
                valid[count][0] = tmpx;
                valid[count][1] = y;
                count++;
                break;
            }
            // if its ur own piece u break
            else if (board[tmpx][y] >= lettera && board[tmpx][y] <= letterz)
                break;
            // if king, break after 1
            if (kingbreak == 1)
                break;
        }
        // right
        for (i = 1; i < 8 - x; i++){
            // cehck if blank
            tmpx = x+i;
            if (board[tmpx][y] == ' '){
                valid[count][0] = tmpx;
                valid[count][1] = y;
                count++;
            }
            // if its a oppoonent, then u put the thing in array and break
            else if (board[tmpx][y] >= letteraop && board[tmpx][y] <= letterzop){
                valid[count][0] = tmpx;
                valid[count][1] = y;
                count++;
                break;
            }
            // if its ur own piece u break
            else if (board[tmpx][y] >= lettera && board[tmpx][y] <= letterz)
                break;
            // if king, break after 1
            if (kingbreak == 1)
                break;
        }
    }
    // check diagonals
    if (board[x][y] != 'R' && board[x][y] - 32 != 'R'){
        // up and right
        for (i = 1; (i < (8 - x)) && (i < (8 - y)); i++){
            // cehck if blank
            tmpx = x+i;
            tmpy = y+i;
            if (board[tmpx][tmpy] == ' '){
                valid[count][0] = tmpx;
                valid[count][1] = tmpy;
                count++;
            }
            // if its a oppoonent, then u put the thing in array and break
            else if (board[tmpx][tmpy] >= letteraop && board[tmpx][tmpy] <= letterzop){
                valid[count][0] = tmpx;
                valid[count][1] = tmpy;
                count++;
                break;
            }
            // if its ur own piece u break
            else if (board[tmpx][tmpy] >= lettera && board[tmpx][tmpy] <= letterz)
                break;
            // if king, break after 1
            if (kingbreak == 1)
                break;
        }
        // down and left
        for (i = 1; (i <= x) && (i <= y); i++){
            // cehck if blank
            tmpx = x-i;
            tmpy = y-i;
            if (board[tmpx][tmpy] == ' '){
                valid[count][0] = tmpx;
                valid[count][1] = tmpy;
                count++;
            }
            // if its a oppoonent, then u put the thing in array and break
            else if (board[tmpx][tmpy] >= letteraop && board[tmpx][tmpy] <= letterzop){
                valid[count][0] = tmpx;
                valid[count][1] = tmpy;
                count++;
                break;
            }
            // if its ur own piece u break
            else if (board[tmpx][tmpy] >= lettera && board[tmpx][tmpy] <= letterz)
                break;
            // if king, break after 1
            if (kingbreak == 1)
                break;
        }
        // up and left
        for (i = 1; (i <= x) && (i < (8 - y)); i++){
            // cehck if blank
            tmpx = x-i;
            tmpy = y+i;
            if (board[tmpx][tmpy] == ' '){
                valid[count][0] = tmpx;
                valid[count][1] = tmpy;
                count++;
            }
            // if its a oppoonent, then u put the thing in array and break
            else if (board[tmpx][tmpy] >= letteraop && board[tmpx][tmpy] <= letterzop){
                valid[count][0] = tmpx;
                valid[count][1] = tmpy;
                count++;
                break;
            }
            // if its ur own piece u break
            else if (board[tmpx][tmpy] >= lettera && board[tmpx][tmpy] <= letterz)
                break;
            // if king, break after 1
            if (kingbreak == 1)
                break;
        }
        // down and right
        for (i = 1; (i < (8 - x)) && (i <= y); i++){
            // cehck if blank
            tmpx = x+i;
            tmpy = y-i;
            if (board[tmpx][tmpy] == ' '){
                valid[count][0] = tmpx;
                valid[count][1] = tmpy;
                count++;
            }
            // if its a oppoonent, then u put the thing in array and break
            else if (board[tmpx][tmpy] >= letteraop && board[tmpx][tmpy] <= letterzop){
                valid[count][0] = tmpx;
                valid[count][1] = tmpy;
                count++;
                break;
            }
            // if its ur own piece u break
            else if (board[tmpx][tmpy] >= lettera && board[tmpx][tmpy] <= letterz)
                break;
            // if king, break after 1
            if (kingbreak == 1)
                break;
        }
    }
    // check for castling of king
    // right black
    if (on == 0)
        return count;
    if (board[x][y] == 'k' && x == 4 && y == 7 && GetRRook(B) == 1 && GetKing(B) == 1 && board[5][7] == ' ' && board[6][7] == ' '){
        // make sure king will not pass check
        if (kingpasscheck('R', board, curcolor, W, B) == 1){
            valid[count][0] = 6;
            valid[count][1] = 7;
            count++;
        }
    }
    // left black
    if (board[x][y] == 'k' && x == 4 && y == 7 && GetLRook(B) == 1 && GetKing(B) == 1 && board[3][7] == ' ' && board[2][7] == ' ' && board[1][7] == ' '){
        // make sure king will not pass check
        if (kingpasscheck('L', board, curcolor, W, B) == 1){
            valid[count][0] = 2;
            valid[count][1] = 7;
            count++;
        }
    }
    // white right
    if (board[x][y] == 'K' && x == 4 && y == 0 && GetRRook(W) == 1 && GetKing(W) == 1 && board[5][0] == ' ' && board[6][0] == ' '){
        // make sure king will not pass check
        if (kingpasscheck('R', board, curcolor, W, B) == 1){
            valid[count][0] = 6;
            valid[count][1] = 0;
            count++;
        }
    }
    // white left
    if (board[x][y] == 'K' && x == 4 && y == 0 && GetLRook(W) == 1 && GetKing(W) == 1 && board[3][0] == ' ' && board[2][0] == ' ' && board[1][0] == ' '){
        // make sure king will not pass check
        if (kingpasscheck('L', board, curcolor, W, B) == 1){
            valid[count][0] = 2;
            valid[count][1] = 0;
            count++;
        }
    }
    return count;    
}

// end of file