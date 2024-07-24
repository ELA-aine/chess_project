#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include "player.h"

#include <vector>
#include <ctime>
#include <map>
#include <string>
#include <iostream>



class ComputerPlayer : public Player {
    int level; 
    bool isWhite;
  public:
    ComputerPlayer(int level, bool isWhite);
    std::string makeMove(std::unique_ptr<Board>& board, const std::string &from, const std::string &to, const std::string &promotion) override;
    std::string level1(std::unique_ptr<Board>& board, bool isWhite);
    std::string level2(std::unique_ptr<Board>& board, bool isWhite);
    std::string level3(std::unique_ptr<Board>& board, bool isWhite);
    std::string level4(std::unique_ptr<Board>& board, bool isWhite, int depth);

};

#endif
