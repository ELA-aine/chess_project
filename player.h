#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "board.h"

// Abstract class for player
// also other #include for each piece, too lazy to put here now

class Player{
  protected:
  bool isWhite; // to determine if the player is assigned white or black pieces

  public:
    Player(bool isWhite) :isWhite(isWhite){} // true = white, false = black 
    virtual void makeMove(Board *board) = 0;
    // determine if player can move or not
    // some other function
    virtual ~Player();
    bool isWhite() const;  // Returns true if the player is White, false if Black

};

#endif



