// board functions

#include "chess_board.h"
#include "chess_struct.h"
#include "chess_move.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// initializes pieces, starts board
void startboard(char board[8][8]){
    int i,j;
    // pawns
    for (i = 0; i < 8; i++){
        board[i][1] = 'P'; 
    }
    // set the blanks in the middle
    for (i = 2; i < 6; i++){
        for (j = 0; j < 8; j++){
            board[j][i] = ' ';
        }
    }
    // pawns and top row
    for (i = 0; i < 8; i++){
        board[i][6] = 'p';
        board[i][7] = board[i][0] + 32;
    }
}

// prints board
void printboard(char board[8][8]){
   int i, j, k;
   // main grid
   // prints 2d array of board
   for (i = 7; i >= 0 ; i--){
     // prints the seperation line
     printf("  ");
     for (k = 0; k < 8; k++){
        printf("+----");
        if (k == 7)
          printf("+");
     }
     printf("\n");
     for (j = 0; j < 8; j++){
         // prints the number on the side first
         if ((j == 0))
            printf("%d |",i + 1);
         // prints the grid too
         if (board[j][i] - 96 > 0)
            printf(" b%c |", board[j][i] - 32);
         else if (board[j][i] - 64 > 0)
            printf(" w%c |", board[j][i]);
         else
            printf("    |");
         
     }
     printf("\n");
   }
   // print last line and letters
   printf("  ");
   for (i = 0; i < 8; i++){
      printf("+");
      printf("----");
      if (i == 7)
        printf("+");
   }
   printf("\n");
   for (j = 0; j < 8; j++)
      printf("    %c", 'a' + j);
   printf("\n");
}

// count and return the points that you color are up
int getPoints(char board[8][8], char color){
    int sumW = 0;
    int sumB = 0;
    int x,y;
    // check the board and count points for colors, pawn = 1, knight = 3, bishop = 3, rook = 5, queen 9, king = 100 (so it doesnt sacrifice it)
    for (x = 0; x < 8; x++){
        for (y = 0; y < 8; y++){
            switch(board[x][y]){
                case 'P':
                    sumW += 30;
                    break;
                case 'p':
                    sumB += 30;
                    break;
                case 'N':
                    sumW += 90;
                    break;
                case 'n':
                    sumB += 90;
                    break;
                case 'B':
                    sumW += 90;
                    break;
                case 'b':
                    sumB += 90;
                    break;
                case 'R':
                    sumW += 150;
                    break;
                case 'r':
                    sumB += 150;
                    break;
                case 'Q':
                    sumW += 282;
                    break;
                case 'q':
                    sumB += 282;
                    break;
                case 'K':
                    sumW += 1777;
                    break;
                case 'k':
                    sumB += 1777;
                    break;
            }
        }
    }
    if (color == 'W')
        return sumW - sumB;
    else
        return sumB - sumW;
}

// replay functions
void Replay(PLAYER *W, PLAYER *B, BMOVE *M, int turn, char color, char winner){
    FILE *fp;
    time_t t;
    int i,j,k,m;
    time(&t);
    fp = fopen("replay.txt","w");
    int currentcolor = 'W';
    char board[8][8] = {{'R'},{'N'},{'B'},{'Q'},{'K'},{'B'},{'N'},{'R'}};
    if (fp == NULL){
       printf("Error Opening File!\n");
       exit(10);
    }
    fprintf(fp,"#Chess_vs_AI\nVersion: 1.0\nFilename: replay.txt\nDate: %s\n",ctime(&t));
    if (GetBot(W) == 1)
         fprintf(fp,"\n#Settings\nWhite (AI): Level %d\n",GetAI(M));
    else
         fprintf(fp,"\n#Settings\nWhite (Player)\n");
    if (GetBot(B) == 1)
         fprintf(fp,"Black (AI): Level %d\n",GetAI(M) + 1);
    else
         fprintf(fp,"Black (Player)\n");
    // winner check
    fprintf(fp,"\n#Winner\n");
    switch(winner){
       case 'D':
          fprintf(fp,"Draw\n");
          break;
       case 'B':
          if (GetBot(W) == 1)
              fprintf(fp,"White (AI)\n");
          else
              fprintf(fp,"White (Player)\n");
          break;
       case 'W':
         if (GetBot(B) == 1)
             fprintf(fp,"Black (AI)\n");
         else
             fprintf(fp,"Black (Player)\n");
         break;
       case 'S':
         fprintf(fp,"Stalemate\n");
         break;
    }
    fprintf(fp,"\n#MovesList\n");
    // print moves list
    for (int i = 0; i < turn*4; i+=4){
          if (currentcolor == 'W'){
              fprintf(fp,"White: %c%c%c%c\n", GetMovesList(M,i) + 'a', GetMovesList(M,i+1) + '1', GetMovesList(M,i+2) + 'a', GetMovesList(M,i+3) + '1');
              currentcolor = 'B';
          }
          else {
              fprintf(fp,"Black: %c%c%c%c\n", GetMovesList(M,i) + 'a', GetMovesList(M,i+1) + '1', GetMovesList(M,i+2) + 'a', GetMovesList(M,i+3) + '1');
              currentcolor = 'W';
          }  
    }
    // board replay
    fprintf(fp,"\n#Replay\n");
    startboard(board);
    fprintf(fp,"Chess game started (Human vs. Human)\n");
    currentcolor = 'W';
    for (m = 0; m < turn*4; m+=4){
          movetoboard(GetMovesList(M,m),GetMovesList(M,m+1), GetMovesList(M,m+2), GetMovesList(M,m+3),board,W,B,1);
          // main grid
          // prints 2d array of board
          for (i = 7; i >= 0 ; i--){
               // prints the seperation line
               fprintf(fp,"  ");
               for (k = 0; k < 8; k++){
                   fprintf(fp,"+----");
                   if (k == 7)
                       fprintf(fp,"+");
               }
               fprintf(fp,"\n");
               for (j = 0; j < 8; j++){
                    // prints the number on the side first
                   if ((j == 0))
                      fprintf(fp,"%d |",i + 1);
                   // prints the grid too
                   if (board[j][i] - 96 > 0)
                      fprintf(fp," b%c |", board[j][i] - 32);
                   else if (board[j][i] - 64 > 0)
                      fprintf(fp," w%c |", board[j][i]);
                   else
                      fprintf(fp,"    |");
               }
               fprintf(fp,"\n");
          }
          // print last line and letters
          fprintf(fp,"  ");
          for (i = 0; i < 8; i++){
              fprintf(fp,"+");
              fprintf(fp,"----");
              if (i == 7)
                 fprintf(fp,"+");
          }
          fprintf(fp,"\n");
          for (j = 0; j < 8; j++)
             fprintf(fp,"    %c", 'a' + j);
          fprintf(fp,"\n");    
          if (currentcolor == 'W'){
              fprintf(fp,"White chose %c%c%c%c!\n", GetMovesList(M,m) + 'a', GetMovesList(M,m+1) + '1', GetMovesList(M,m+2) + 'a', GetMovesList(M,m+3) + '1');
              currentcolor = 'B';
          }
          else {
              fprintf(fp,"Black chose %c%c%c%c!\n", GetMovesList(M,m) + 'a', GetMovesList(M,m+1) + '1', GetMovesList(M,m+2) + 'a', GetMovesList(M,m+3) + '1');
              currentcolor = 'W'; 
          }
    }
    if (winner == 'B'){
       if (GetBot(W) == 0)
           fprintf(fp,"\nWhite (Player) Wins!\n");
       else
           fprintf(fp,"\nWhite (AI) Wins!\n");
    }
    else if (winner == 'W'){
       if (GetBot(B) == 0)
           fprintf(fp,"\nBlack (Player) Wins!\n");
       else
           fprintf(fp,"\nBlack (AI) Wins!\n");
    }
    else
       fprintf(fp,"\nNo one wins!\n");
    fprintf(fp,"\n#EOF");
    fclose(fp);
}
// end of file