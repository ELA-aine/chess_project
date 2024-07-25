#include <iostream>
#include <string>
#include "Game.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <memory>

/*
int main() {
  
  bool isGame = false;



    Board *board;
    string command;
    Game game;

    if (!isGame && command != "game") {
      cout << "Please start a game before you do further steps" << endl;
    } els

    while(cin >> command) {
      
      /////// If not in game, then setup mode or let user create a new game ///////
      if (!isGame) {
        if (command == "setup") {
          string action;
          while (cin >> action) {
            char piece;
            string coord;
            string colour;
            if (action == "+") {
              cin << piece << coord;
              game.setBoard(char piece, string coord);
              game.display();
            } else if (action == "-") {
              game.removeCoord(string coord);
              game.display();
            } else if (action == "=") {
              .... don't know what to do
            } else if (action == "done") {
              break;
            }
          }
        } else if (command != "game") {
          cout << "Please start a game before you do further steps" << endl;
          continue;
        }
      } 

      ////////// if it is game, create game or make further movement ///////////
      if (command == "game") {
        string whiteplayer;
        string blackplayer;
        int level = 0;
        cin << whiteplayer << blackplayer;
        game = new Game(board, level, whiteplayer, blackplayer);
        isGame = true;
      } else if (command == "move") {
        game.changePlayer();
        string start;
        string end;
        cin << start << end;
        bool valid = game.move(start, end);
        if (!valid) {
          cout >> "not valid move, move again";
        } else {
          game.display();
        }
      } else if (command == "resign") {
        game.isWinner(string OppositeWinner)         //not know how to decide;
        isGame = false;
      } 
  
}

  */ 

#include <iostream>
#include <string>
#include "Game.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"

// below is basically the same as the code elaine written, but i am trying to complete it. I also try to embed the set-up to be implemented by game so it looked cleaner, and differs a bit in terms of handling the computer level logic. subject to changes !

int stringToInt(std::string) {
  // ...
}

int main() {
    Game game;

    std::string command;
    while (std::cin >> command) {
       // starting a game 
        if (command == "game") {
            std::string whitePlayerType, blackPlayerType;
            std::cin >> whitePlayerType >> blackPlayerType; // so the contract is always the first type string after game is whitePlayer, and second is blackPlayer, option: [human/computer] like Elaine wrote

            std::unique_ptr<Player> whitePlayer = nullptr;; // initialize a new string to Player type
            std:unique_ptr<Player> blackPlayer = nullptr; 

            if (whitePlayerType == "human") { // the logic here is to set the Player correctly according to type
               whitePlayer = std::make_unique<HumanPlayer>(true); // constructor 
            } else if (whitePlayerType.rfind("computer", 0) == 0) { // we are writing the level like computer1 computer2 etc so this line checks if the first substring is computer.
                int level = stringToInt(whitePlayerType.substr(8)); // then we could check the last number and convert it to interger
                whitePlayer = std::make_unique<ComputerPlayer> (true, level); 
            }

            if (blackPlayerType == "human") {
                blackPlayer = std::make_unique<HumanPlayer>(false);;
            } else if (blackPlayerType.rfind("computer", 0) == 0) {
                int level = std::stoi(blackPlayerType.substr(8));
                blackPlayer = std::make_unique<ComputerPlayer> (false, level); // i think through it and agree with patricia, using boolean to represent whether it is black or white is easier when constructing a player. i use false for black and true for white. we could discuss further. 
            }

            game.start(std::move(whitePlayer), std::move(blackPlayer)); // I am assuming this will create a copy of the players so i delete the players next line.

            // Clean up dynamically allocated memory

        } else if (command == "move") {
            std::string from, to, promotion;
            std::cin >> from >> to;
            if (std::cin.peek() != '\n') { // each command line is separated by a newline character
                std::cin >> promotion;
            }
            game.makeMove(from, to, promotion); // promotion can be set as a optional parameter, because not every move could be promotion
        } else if (command == "resign") {
            game.resign();
        } else if (command == "setup") { // look at Elaine's code
            game.setup();
        } else if (command == "undo") {
            game.undoMove();
        }
    }

    game.printFinalScore();
    return 0;
}

// example command:

// game 
// human
// computer3 // black is computer level 3
// move e2 e4 // white
// move something something // black
// ...
// move e7 e8 Q // promotion
// ... 
// resign // I am tired of chess and Waterloo ughhh
