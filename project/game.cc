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

void Game::makeMove(const string &from, const string &to, const string &promotion) {
  //char thePiece = board->getPiece(from)->getSymbol();
  cout << "Current turn is: " << white << endl;
  if (white) {
    bool valid = player1->makeMove(board, from, to, promotion);
    if (!valid) {
      cout << "not valid" << endl;
    } else {
      changePlayer();
    }
  } else {
    bool valid = player2->makeMove(board, from, to, promotion);
    if (!valid) {
      cout << "not valid" << endl;
    } else {
      changePlayer();
    }
  }
    

  
  display();
}


void Game::changePlayer() {
  white = !white;
  cout << "It's" ;
  if (white) {
    cout << "white turn" << endl;
  } else {
    cout << "black turn" << endl;
  }
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
  if(!white) {
    cout << "CheckMate! white wins!" << endl;
    addScore(true);
    end();
  } else {
    cout << "CheckMate! Black wins!" << endl;
    addScore(false);
    end();
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

void Game::end() {
  cout << "The game has ended." << endl;
    printFinalScore();
    // Reset the game state if necessary
    board = make_unique<Board>();
    player1.reset();
    player2.reset();
    white = true;
}
