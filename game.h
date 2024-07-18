#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "board.h"
#include "piece.h"
#include <map>
#include <string>

using namespace std;

// Creat a "Actual" Chess game

class Game{
  int level = 0;          // set level to the game. 0 means human player, anything from 1-4 means computer player
  Board *board;           // the game board, see board.h for documentation
  Player *player1;        // player1, human/computer
  Player *player2;        // player2, human/computer       
  bool isWhite = true;    // current player. Default starts from white

   class Vec{             // this class is for storing the coordinate.        
    public:               // although coordinate's input is char + int, but we can convert char to int
    int x, y;             //    so that we could iterate over the board easily
  };


  vector<string, Vec> whiteHistory;          // move history for white player
  vector<string, Vec> blackHistory;          // move history for black player
  map<string, int> scoreBoard;            // score board for white player and black player

  public:
    Game(); 
    void start(Player *white, Player *black);     
      // constructor of game, use string to decide what player we have for white and black
      //    and initialize the field accordingly
    void makeMove(const string &from, const string &to, const string &promotion = ""); 
      // if CHECKMATE -> isWinner(whoever play)
      // if CHECK -> I don't know
      // else:
      //  move the piece of it is valid, true could be valid, false is not valid
      //    based on current player
      // if valid, add the move to corresponding history.
    void display();// output the board
    bool isCheck();
    //check bincheck (may be put in King class)
    bool isCheckMate();
      // lost the game
    void changePlayer();      
    // change to !White to keep track of current player
    // Note: I don't know if we really need a function to set isWhite to !isWhite (and vice versa)
    //       this is just a function to keep track what current player is so that we could use
    //       PLAYER's method accordingly.
    void isWinner(string player);         
    // display the winner message, set the winner score + 1;
    void addScore(string player);
    // set player's score + 1;
    void resign(); // self-explanatory 
    void printFinalScore() const; // self-explanatory
    void setup(); // Elaine's idea

    //////////// Additional function for Additional feature, if needed ///////////////

    void undo();
    // delete last move from the history, and change the board accordingly
    void displayLastMove();
    // display last move from the history accordingly
    void analyze();
    // analyze current board and output possible move to output stream;
    // other additional method can be added
    

};

#endif
