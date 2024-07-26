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

void Game::makeMove(const string &from, const string &to, const string &promotion) const {
    cout << "Current turn is: " << (isWhite ? "White" : "Black") << endl;

    bool valid;
    if (isWhite) {
      if(canEnPassant){
        valid = player1->makeMove(board, from, to, promotion);
      }
    } else {
        valid = player2->makeMove(board, from, to, promotion);
    }

    if (!valid) {
        cout << "Invalid move" << endl;
        return; // Exit the function if the move is invalid
    }

    // Check if the king is in check after the move
    bool isKingInCheck = board->isInCheck(!isWhite);
    if (isKingInCheck) {
        cout << "King is in check!" << endl;
        if(board->isInCheckmate(!isWhite)) {
          isWinner(isWhite);
        }
    }

    // check stalemate (every pieces has no possible moves but not check)
    if(board->isStalemate(!isWhite)) {
      cout << "The game is draw!" << endl;
    }

    // Change the player if the move is valid and no check condition
    changePlayer();
}


bool Game::isCheck() const{
  if (isWhite && board->isInCheck(true)) {
    return true;
  } else if (!isWhite && board->isInCheck(false)) {
    return true;
  } else {
    return false;
  }
}

bool Game::isCheckMate() const{
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

void Game::changePlayer() const {
  isWhite = !isWhite;
}

void Game::isWinner(bool white) const{
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
