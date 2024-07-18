#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "player.h"



class HumanPlayer : public Player {
  public:
  HumanPlayer(bool isWhite);
  void makeMove(Board *board) override;
};

#endif

