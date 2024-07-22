#include "game.h"
using namespace std;

Game::Game(){
  board = make_unique<Board>();
  scoreBoard["white"] = 0;
  scoreBoard["black"] = 0;
}

void Game::start(unique_ptr<Player> white, unique_ptr<Player> black) {
  player1 = move(white);
  player2 = move(black);
  board->init();
  display();
}

void Game::makeMove(const string &from, const string &to, const string &promotion = "") {
  char thePiece = board->getPiece(from).getSymbol();
  bool valid = board->getPiece(from).isValidMove(from, to, board);
  Vec toCoord = {from, to};
  
  if (!valid) {
    cout << "Not valid move, move again" << endl;
  }

   if (isWhite) {
        whiteHistory.push_back({thePiece, toCoord});
    } else {
        blackHistory.push_back({thePiece, toCoord});
    }
    
    changePlayer();
    display();
}

bool Game::isCheck() {
  return false;
}

bool Game::isCheckMate() {
  if (isWhite && board->isInCheckmate(true)) {
    isWinner(false);
    return true;
  } else if (!isWhite && board->isInCheckmate(false)) {
    isWinner(true);
    return true;
  } else {
    return false;
  }
}

void Game::changePlayer() {
  isWhite = !isWhite;
}

void Game::isWinner(bool white) {
  if(white) {
    cout << "CheckMate! White wins!" << endl;
    addScore(true);
  } else {
    cout << "CheckMate! Black wins!" << endl;
    addScore(false);
  }
}

void Game::addScore(bool white) {
  if (white) {
    scoreBoard["white"] += 1;
  } else {
    scoreBoard["black"] += 1;
  }
}

void Game::resign() {
  if(!isWhite) {
    cout << "CheckMate! white wins!" << endl;
    addScore(true);
  } else {
    cout << "CheckMate! Black wins!" << endl;
    addScore(false);
  }
}

void Game::printFinalScore() {
  cout << "Final Score:" << endl;
  cout << "White: " << scoreBoard["white"] << endl;
  cout << "Black: " << scoreBoard["black"] << endl;
}

void Game::setup() {
  board->setupBoard();
}

void Game::display() {
  board->display();
}