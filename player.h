#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "board.h"

// Abstract class for player
// also other #include for each piece, too lazy to put here now

class Player{
  protected:
  Board *board; 
  bool isWhite; // to determine if the player is assigned white or black pieces
  int level;    // determine the level played;

  public:
    Player(int level, bool isWhite) :isWhite(isWhite), level{level}{}
    virtual bool isMove(string coord);
    // determine if player can move or not
  // some other function
};

#endif

