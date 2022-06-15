// chess structure functions

#include "chess_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// new player
PLAYER *NewPlayer(int botornot){
     PLAYER *pl;
     pl = malloc(sizeof(*pl));
     if (!pl){
        perror("Out of memory! Exiting...");
        return(NULL);
     }
     pl->botornot = botornot;
     pl->passantx = 10;
     pl->kingflag = 1;
     pl->rrookflag = 1;
     pl->lrookflag = 1;
     pl->storedinfo = malloc(128);
     return pl;
}

// new move
BMOVE *NewMove(){
     BMOVE *m;
     m = malloc(sizeof(*m));
     if (!m){
        perror("Out of memory! Exiting...");
        return(NULL);
     }
     m->bestx = 0;
     m->besty = 0;
     m->besti = 0;
     m->bestj = 0;
     m->level = 0;
     m->currentpiece = '0';
     m->repeatcheck = 0;
     m->storedrepeat = malloc(64);
     m->storedmoves = malloc(1024);
     return m;
}

// delete player
void DeletePlayer(PLAYER *pl){
    assert(pl->storedinfo);
    free(pl->storedinfo);
    assert(pl);
    free(pl);
}

// delete move
void DeleteMove(BMOVE *m){
    assert(m->storedrepeat);
    free(m->storedrepeat);
    assert(m->storedmoves);
    free(m->storedmoves);
    assert(m);
    free(m);
}

// set move stuff
void SetX(BMOVE *m, int n){
    m->bestx = n;
}

void SetY(BMOVE *m, int n){
    m->besty = n;
}

void SetI(BMOVE *m, int n){
    m->besti = n;
}

void SetJ(BMOVE *m, int n){
    m->bestj = n;
}

// get move stuff
int GetX(const BMOVE *m){
    return (m->bestx);
}

int GetY(const BMOVE *m){
    return (m->besty);
}

int GetI(const BMOVE *m){
    return (m->besti);
}

int GetJ(const BMOVE *m){
    return (m->bestj);
}

// set bot
void SetBot(PLAYER *pl, int i){
    pl->botornot = i;
}

// get bot
int GetBot(const PLAYER *pl){
    return(pl->botornot);
}

// set castle indicators
void SetRRook(PLAYER *pl){
    pl->rrookflag = 0;
}

void SetLRook(PLAYER *pl){
    pl->lrookflag = 0;
}

void SetKing(PLAYER *pl){
    pl->kingflag = 0;
}

// get castle indicators
int GetRRook(const PLAYER *pl){
    return(pl->rrookflag);
}

int GetLRook(const PLAYER *pl){
    return(pl->lrookflag);
}

int GetKing(const PLAYER *pl){
    return(pl->kingflag);
}

//set passant move
void SetPassant(PLAYER *pl, int x){
     pl->passantx = x;
}

// get passant move
int GetPassantX(const PLAYER *pl){
    return(pl->passantx);
}

// stores info
void StoreInfo(PLAYER *pl, int i){
    // allocates ahead
    int pos = i*5;
    *(pl->storedinfo + pos) = pl->passantx;
    *(pl->storedinfo + 1 + pos) = pl->kingflag;
    *(pl->storedinfo + 2 + pos) = pl->rrookflag;
    *(pl->storedinfo + 3 + pos) = pl->lrookflag;
}

// puts the stored info back into the player
void GetInfo(PLAYER *pl, int i){
    int pos = i*5;
    pl->passantx = *(pl->storedinfo + pos);
    pl->kingflag = *(pl->storedinfo + 1 + pos);
    pl->rrookflag = *(pl->storedinfo + 2 + pos);
    pl->lrookflag = *(pl->storedinfo + 3 + pos);
}

// stores info
void StoreRInfo(BMOVE *m, int i){
    // allocates ahead
    *(m->storedrepeat + i) = m->repeatcheck;
}

// puts the stored info back into the move
void GetRInfo(BMOVE *m, int i){
    m->repeatcheck = *(m->storedrepeat + i);
}


// set repeat 
void SetRepeat(BMOVE *m, int i){
    m->repeatcheck = i;
}

// get repeat
int GetRepeat(const BMOVE *m){
    return(m->repeatcheck);
}

// set piece 
void SetPiece(BMOVE *m, char i){
    m->currentpiece = i;
}

// get piece
char GetPiece(const BMOVE *m){
    return(m->currentpiece);
}

// ai levels
void SetAI(BMOVE *m, int i){
    m->level = i;
}

int GetAI(const BMOVE *m){
    return(m->level);
}

// moves list
void SetMovesList(BMOVE *m, int x, int y, int i, int j, int turn){
    int pos = turn*4;
    *(m->storedmoves + pos) = x;
    *(m->storedmoves + 1 + pos) = y;
    *(m->storedmoves + 2 + pos) = i;
    *(m->storedmoves + 3 + pos) = j;
}  

int GetMovesList(BMOVE *m, int n){
    return *(m->storedmoves + n);
}

// end of file