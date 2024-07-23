#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "board.h"

#include "king.h"
#include "queen.h"
#include "knight.h"
#include "pawn.h"
#include "rook.h"
#include "bishop.h"

// Abstract class for player

class Player{
  protected:
  bool isWhite; // to determine if the player is assigned white or black pieces

  public:
    Player(bool isWhite) :isWhite(isWhite){} // true = white, false = black 
    virtual std::string makeMove(Board *board) = 0;
    // determine if player can move or not
    // some other function
    virtual ~Player();
    bool isWhite() const;  // Returns true if the player is White, false if Black

};

#endif



