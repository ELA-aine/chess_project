#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "player.h"



class HumanPlayer : public Player {
  public:
  HumanPlayer(int level = 0, bool isWhite);
  bool ismove(string coord);
};

#endif
