#include <iostream>
#include "game.h"
#include "board.h"
#include "player.h"
#include "humanplayer.h"
//#include "move.h"
#include "piece.h"
#include "pawn.h"

int main() {
    Game game;

    std::string command;
    while (std::cin >> command) {
       // starting a game 
        if (command == "game") {
            std::string whitePlayerType, blackPlayerType;
            std::cin >> whitePlayerType >> blackPlayerType; // so the contract is always the first type string after game is whitePlayer, and second is blackPlayer, option: [human/computer] like Elaine wrote
            unique_ptr<Player> whitePlayer, blackPlayer;
            

            if (whitePlayerType == "human") { // the logic here is to set the Player correctly according to type
                whitePlayer = make_unique<HumanPlayer>(true); // constructor 
            } else {
                continue;
            }

            if (blackPlayerType == "human") {
                blackPlayer = make_unique<HumanPlayer>(false);
            } else {
                continue;
            }

            game.start(move(whitePlayer), move(blackPlayer)); // I am assuming this will create a copy of the players so i delete the players next line.

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
        } else {
        } 
    }

    game.printFinalScore();
    return 0;
}

