// chess structure header
// contains anything that has to do with the structures of the program

#ifndef CHESS_STRUCT_H
#define CHESS_STRUCT_H

// structures
typedef struct player PLAYER;   // player info structure
typedef struct bestmove BMOVE;  // best move info

// structure of player
struct player {
        int botornot;          // 0 if its human, 1 if its bot
        int passantx;          // column where a pawn is that can be passanted
        int kingflag;          // checks if king has moved, 1 if has not moved and can castle, default
        int rrookflag;         // checks if right rok can castle
        int lrookflag;         // checks if left rook can castle
        char *storedinfo;      // stores info so temp arrays dont mess with it
};

// current best move for the AI, 
struct bestmove {
        int bestx; // column of piece moving
        int besty; // row of piece moving
        int besti; // column of where piece move to
        int bestj; // row of where piece move to
        int level; // level of the AI
        char currentpiece; // what the current piece they r trying to move, so it can check if repetition
        int repeatcheck; // checks for too many repeated moves
        char *storedrepeat; // store repeat info
        char *storedmoves; // list of stored moves
};

// player structure
PLAYER *NewPlayer(int botornot);

// move structure
BMOVE *NewMove();

// delete player
void DeletePlayer(PLAYER *pl);

// delete move
void DeleteMove(BMOVE *m);

// set coordinates for move
void SetX(BMOVE *m, int n);

void SetY(BMOVE *m, int n);

void SetI(BMOVE *m, int n);

void SetJ(BMOVE *m, int n);

// get coordinates for move
int GetX(const BMOVE *m);

int GetY(const BMOVE *m);

int GetI(const BMOVE *m);

int GetJ(const BMOVE *m);

// set checks for special moves and regular check
void SetRRook(PLAYER *pl);

void SetLRook(PLAYER *pl);

void SetKing(PLAYER *pl);

// get checks for special moves and regular check
int GetRRook(const PLAYER *pl);

int GetLRook(const PLAYER *pl);

int GetKing(const PLAYER *pl);

// store info
void StoreInfo(PLAYER *pl, int i);

// get info
void GetInfo(PLAYER *pl, int i);

// set bot
void SetBot(PLAYER *pl, int i);

// get if bot
int GetBot(const PLAYER *pl);

// set passant column
void SetPassant(PLAYER *pl, int x);

// get passant column
int GetPassantX(const PLAYER *pl);

// set repeat 
void SetRepeat(BMOVE *m, int i);

// get repeat
int GetRepeat(const BMOVE *m);

// set piece 
void SetPiece(BMOVE *m, char i);

// get piece
char GetPiece(const BMOVE *m);

// ai levels
void SetAI(BMOVE *m, int i);

int GetAI(const BMOVE *m);

// stores info
void StoreRInfo(BMOVE *m, int i);

// puts the stored info back into the move
void GetRInfo(BMOVE *m, int i);

// moves list
void SetMovesList(BMOVE *m, int x, int y, int i, int j, int turn);

int GetMovesList(BMOVE *m, int n);

#endif // chess struct