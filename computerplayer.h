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

#endif
