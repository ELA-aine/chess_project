#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "player.h"



class HumanPlayer : public Player {
  public:
  HumanPlayer(bool isWhite, int level = 0);
  bool ismove(string coord);
};

#endif

// #ifndef HUMANPLAYER_H
// #define HUMANPLAYER_H

// #include "Player.h"

// class HumanPlayer : public Player {
// public:
//     HumanPlayer(bool isWhite);  // Constructor: Initializes HumanPlayer with color
//     void makeMove(Board *board) override;  // Overrides the makeMove method to handle human input

// private:
//     // You can add more private members if needed for handling human-specific logic
// };

// #endif // HUMANPLAYER_H
