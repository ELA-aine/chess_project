#include <vector>
#include <map>
#include <string>
#include <iostream>

using namespace std;

class Board {
  int[8][8] board;

  class Vec{
    public:
    string player;
    int x, int y;
  };

  map<string, Vec> boardHistory;

  Board(....)
  public:
  void init();
  bool moveOrNot(Piece *whatPiece, int startX, int startY, int endX, int endY);
    //move the piece of it is valid, true could be valid, false is not valid
  void display() (or ostream)
  bool isCheck()
  //check bincheck (may be put in King class)
  bool isCheckMate()
    // lost the game
};
   



