#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include "player.h"



class ComputerPlayer : public Player {
  int level;
  public:
  ComputerPlayer(int level, bool isWhite);
  void makeMove(Board *board) override;
};

#endif
