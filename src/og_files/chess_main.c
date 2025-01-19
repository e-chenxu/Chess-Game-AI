// main file with menu functions and menu

#include "chess_struct.h"
#include "chess_board.h"
#include "chess_move.h"
#include "chess_AI.h"
#include "chess_checks.h"
#include <stdio.h>

// bot games and human vs human
void botgame();
void humangame();
void botvbotgame();

void botgame(){
    // initialize boards first row and player structure move struture
    PLAYER *W, *B;
    BMOVE *M;
    W = NewPlayer(0);
    B = NewPlayer(1);
    M = NewMove();
    char op;
    int opt,x,y,i,j;
    printf("What color would you like to play? (Type 'W' or 'B'): ");
    scanf(" %c", &op);
    if (op == 'B'){
        SetBot(W, 1);
        SetBot(B, 0);
    }
    printf("What level AI would you like to play against? (Input an integer 1-10): ");
    scanf(" %d", &opt);
    if (opt > 0 && opt < 12){
        SetAI(M, opt - 1);
    }
    char board[8][8] = {{'R'},{'N'},{'B'},{'Q'},{'K'},{'B'},{'N'},{'R'}};
    char input[5];
    startboard(board);
    printf("Chess game started (Human vs. AI)\n");
    printboard(board);
    char currentcolor = 'W';
    int turn = 0;
    int movecheck = 0;
    char winnerflag = 'D';
    int currentbot = GetBot(W);

    // human vs ai
    while(1){
        if (currentbot == 0){
            do {
                if (currentcolor == 'W')
                    printf("White, please input your move: ");
                else
                    printf("Black, please input your move: ");
                scanf("%s",input);
                movecheck = moveinput(input,board,currentcolor, W, B);
            } while(movecheck == 0);
            if (movecheck == 2)
                break;
            printboard(board);
            if (currentcolor == 'W')
                printf("White chose %s!\n", input);
            else 
                printf("Black chose %s!\n", input);
        }
        else {
            // bot stuff
            printf("Calculating move...\n");
            bestbotmove(board,currentcolor,W,B,M);
            printboard(board);
            if (currentcolor == 'W')
                printf("White chose %c%c%c%c!\n", GetX(M) + 'a', GetY(M) + '1', GetI(M) + 'a', GetJ(M) + '1');
            else
                printf("Black chose %c%c%c%c!\n", GetX(M) + 'a', GetY(M) + '1', GetI(M) + 'a', GetJ(M) + '1');
        }
        // switch bot and current color
        if (currentbot == 0){
             x = input[0] - 'a';
             y = input[1] - '1'; 
             i = input[2] - 'a';
             j = input[3] - '1';
             SetMovesList(M, x, y, i, j, turn);
             currentbot = 1;
        }
        else{
            SetMovesList(M, GetX(M), GetY(M), GetI(M), GetJ(M), turn);
            currentbot = 0;
        }
        turn++;
        if (currentcolor == 'W')
            currentcolor = 'B';
        else 
            currentcolor = 'W';
        // check end conditions
        if  (winnercheck(board, currentcolor, W, B) == 1){
            if (currentcolor == 'W'){
                printf("Checkmate! Black Wins!\n");
                winnerflag = 'B';
            }
            else {
                printf("Checkmate! White Wins!\n");
                winnerflag = 'W';
            }
            break;
        }
        else if (winnercheck(board, currentcolor, W, B) == 2){
            printf("It's a stalemate!\n");
            winnerflag = 'S';
            break;
        }
    }
    printf("Save replay? (Type 'Y' or 'N'): ");
    scanf(" %c",&op);
    if (op == 'Y'){
       SetAI(M,opt-1);
       Replay(W, B, M, turn, currentcolor,winnerflag);
       printf("Saved replay to 'replay.txt'\n\n");
    }
    DeletePlayer(W);
    DeletePlayer(B);
    DeleteMove(M);
}

// human vs human
void humangame(){
    int x,y,i,j;
    // initialize boards first row and player structure move struture
    PLAYER *W, *B;
    BMOVE *M;
    W = NewPlayer(0);
    B = NewPlayer(0);
    M = NewMove();
    char board[8][8] = {{'R'},{'N'},{'B'},{'Q'},{'K'},{'B'},{'N'},{'R'}};
    char input[5];
    char op;
    startboard(board);
    printf("Chess game started (Human vs. Human)\n");
    printboard(board);
    char currentcolor = 'W';
    char winnerflag = 'D';
    int movecheck = 0;
    int turn = 0;
    while(1){
        do {
            if (currentcolor == 'W')
                printf("White, please input your move: ");
            else
                printf("Black, please input your move: ");
            scanf("%s",input);
            movecheck = moveinput(input,board,currentcolor, W, B);
        } while(movecheck == 0);
        if (movecheck == 2)
            break;
        printboard(board);
        x = input[0] - 'a';
        y = input[1] - '1'; 
        i = input[2] - 'a';
        j = input[3] - '1';
        SetMovesList(M, x, y, i, j, turn);
        turn++;
        if (currentcolor == 'W'){
            printf("White chose %s!\n", input);
            currentcolor = 'B';
        }
        else {
            printf("Black chose %s!\n", input);
            currentcolor = 'W';
        }
        if (winnercheck(board, currentcolor, W, B) == 1){
            if (currentcolor == 'W'){
                printf("Checkmate! Black Wins!\n");
                winnerflag = 'B';
            }
            else {
                printf("Checkmate! White Wins!\n");
                winnerflag = 'W';
            }
            break;
        }
        else if (winnercheck(board, currentcolor, W, B) == 2){
            printf("It's a stalemate!\n");
            winnerflag = 'S';
            break;
        }
    }
    printf("Save replay? (Type 'Y' or 'N'): ");
    scanf(" %c",&op);
    if (op == 'Y'){
       Replay(W, B, M, turn, currentcolor,winnerflag);
       printf("Saved replay to 'replay.txt'\n\n");
    } 
    DeletePlayer(W);
    DeletePlayer(B);
    DeleteMove(M);
}

void botvbotgame(){
    // initialize boards first row and player structure move struture
    PLAYER *W, *B;
    BMOVE *M;
    W = NewPlayer(1);
    B = NewPlayer(1);
    M = NewMove();
    char op;
    int opt;
    printf("What level would you like the AIs to be? (Input an integer 1-10): ");
    scanf(" %d", &opt);
    if (opt > 0 && opt < 12){
        SetAI(M, opt - 1);
    }
    char board[8][8] = {{'R'},{'N'},{'B'},{'Q'},{'K'},{'B'},{'N'},{'R'}};
    startboard(board);
    printf("Chess game started (AI vs. AI)\n");
    printboard(board);
    char currentcolor = 'W';
    int turn = 0;
    char winnerflag = 'D';

    // ai vs ai
    while(1){
        // calculate bot move
        printf("Calculating move...\n");
        bestbotmove(board,currentcolor,W,B,M);
        printboard(board);
        if (currentcolor == 'W')
            printf("White chose %c%c%c%c!\n", GetX(M) + 'a', GetY(M) + '1', GetI(M) + 'a', GetJ(M) + '1');
        else
            printf("Black chose %c%c%c%c!\n", GetX(M) + 'a', GetY(M) + '1', GetI(M) + 'a', GetJ(M) + '1');
        // switch bot and current color
        SetMovesList(M, GetX(M), GetY(M), GetI(M), GetJ(M), turn);
        turn++;
        if (currentcolor == 'W')
            currentcolor = 'B';
        else
            currentcolor = 'W';
        // check end conditions
        if  (winnercheck(board, currentcolor, W, B) == 1){
            if (currentcolor == 'W'){
                printf("Checkmate! Black Wins!\n");
                winnerflag = 'B';
            }
            else {
                printf("Checkmate! White Wins!\n");
                winnerflag = 'W';
            }
            break;
        }
        else if (winnercheck(board, currentcolor, W, B) == 2){
            printf("It's a stalemate!\n");
            winnerflag = 'S';
            break;
        }
    }
    printf("Save replay? (Type 'Y' or 'N'): ");
    scanf(" %c",&op);
    if (op == 'Y'){
        SetAI(M,opt-1);
        Replay(W, B, M, turn, currentcolor,winnerflag);
        printf("Saved replay to 'replay.txt'\n\n");
    }
    DeletePlayer(W);
    DeletePlayer(B);
    DeleteMove(M);
}

int main(void){
   int op;
   // loops through program until exit condition
   while(1){
        printf("\nWelcome to Chess_vs_AI!\n");
        printf("How to Play: Type the coordinates of what you want to move and where you want to move to. Ex. 'a2a4'\n");
        printf("1. Start New Game (Human vs. Human)\n");
        printf("2. Start New Game (Human vs. AI)\n");
        printf("3. Watch New Game (AI vs. AI)\n");
        printf("4. Exit Game (Also Enter '0' When In-Game to Exit Early)\n");
        printf("Choose option: ");
        scanf(" %d", &op);
        switch(op){
        case 1:
            humangame();
            break;
        case 2:
            botgame();
            break;
        case 3:
            botvbotgame();
            break;
        case 4:
            printf("Goodbye!\n");
            return 0;
        }
   }
}

// end of file