#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "knight.h"
#include "pawn.h"
#include "rook.h"
#include "bishop.h"

using namespace std;

class Board {
  int board[8][8];

  class Vec{
    public:
    string player;
    int x, y;
  };

  map<string, Vec> boardHistory;

  
  public:
  Board();
  
  void init();
  bool moveOrNot(Piece *whatPiece, int startX, int startY, int endX, int endY);
    //move the piece of it is valid, true could be valid, false is not valid
  void display();// (or ostream)
  bool isCheck();
  //check bincheck (may be put in King class)
  bool isCheckMate();
    // lost the game
};
   



