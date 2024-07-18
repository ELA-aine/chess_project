#include <map>
#include <iostream>

// other necessary #includes

using namespace std;


int main() {
  
  bool isGame = false;


  /*
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
  */ 
  
}