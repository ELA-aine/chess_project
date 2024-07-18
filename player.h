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
    Player(bool isWhite, int level) :isWhite(isWhite), level{level}{} // true = white, false = black 
    virtual bool isMove(string coord);
    // determine if player can move or not
    // some other function
};

#endif

// #ifndef PLAYER_H
// #define PLAYER_H

// #include "Board.h"

// class Player {
// public:
//     Player(bool isWhite);  // Constructor: Initializes the player with color (White or Black)
//     virtual ~Player();  // Virtual destructor for proper cleanup of derived classes
//     virtual void makeMove(Board *board) = 0;  // Pure virtual method: Derived classes must implement this to make a move

//     bool isWhite() const;  // Returns true if the player is White, false if Black

// private:
//     bool white;  // Boolean flag to indicate if the player is White (true) or Black (false)
// };

// #endif // PLAYER_H


