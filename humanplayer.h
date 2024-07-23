#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "player.h"

#include <vector>
#include <map>
#include <string>
#include <iostream>



class HumanPlayer : public Player {
  bool isWhite;
  
  public:
  HumanPlayer(bool isWhite);
  std::string makeMove(Board *board) override;
};

#endif

