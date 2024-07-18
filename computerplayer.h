#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include "player.h"



class ComputerPlayer : public Player {
  public:
  ComputerPlayer(int level, bool isWhite);
  bool isMove(string coord);

  /*
    Question:
      I was thinking for computer's move, do we do different move function for each level? 
  */
};

#ifndef HUMANPLAYER_H
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


// #endif
