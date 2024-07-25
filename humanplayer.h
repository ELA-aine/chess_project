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
  std::string makeMove(Board *board, const std::string &from, const std::string &to, const std::string &promotion) override;
};

#endif

