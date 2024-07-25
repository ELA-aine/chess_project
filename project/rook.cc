#include "rook.h"
#include <cmath>


Rook::Rook(bool isWhite, char symbol) : Piece(isWhite, symbol), moved(false) {}


/* bool Rook::isValidMove(const std::string &from, const std::string &to) const {
   // Convert board coordinates from string to numeric
   int fromX = from[0] - 'a';
   int fromY = from[1] - '1';
   int toX = to[0] - 'a';
   int toY = to[1] - '1';


   // so a1 -> (0,0) b1 -> (1,0)
   // Check if move is horizontal or vertical
   if (fromX == toX || fromY == toY) {
       return true; // The move is valid
   }
   return false; // The move is not horizontal or vertical
} */

bool Rook::isValidMove(const std::string &from, const std::string &to) const {
   // Convert board coordinates from string to numeric
   int fromX = from[0] - 'a';
   int fromY = from[1] - '1';
   int toX = to[0] - 'a';
   int toY = to[1] - '1';


   // so a1 -> (0,0) b1 -> (1,0)


   // Check if move is horizontal or vertical
   if (fromX == toX || fromY == toY) {
       // Check if there are any pieces blocking the path
       // For horizontal moves
       if (fromY == toY) {
           return true;
       }
       // For vertical moves
       else if (fromX == toX) {
           return true;
       }
       return true; // The move is valid
   }


   return false; // The move is not horizontal or vertical
}




// Provides the symbol for the Rook
char Rook::getSymbol() const {
   return this->symbol; // 'Q' for white queen, 'q' for black queen
}


bool Rook::hasMoved() const {
   return moved;
}


void Rook::setMoved(bool moved) {
   this->moved = moved;
}
