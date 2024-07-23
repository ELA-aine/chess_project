#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include "player.h"

#include <vector>
#include <map>
#include <string>
#include <iostream>



class ComputerPlayer : public Player {
    int level; 
  public:
    ComputerPlayer(int level, bool isWhite);
    std::string makeMove(Board *board) override;
    std::string level1(Board board);

};

#endif
