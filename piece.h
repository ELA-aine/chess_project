// #ifndef PIECE_H
// #define PIECE_H
// #include <string>
// #include "board.h"
// using namespace std;

// class Piece {
//   protected:
//     bool white;
//     char symbol;
//   public:
//     Piece(bool isWhite, char symbol);
//     virtual bool isValidMove(const std::string &from, const std::string &to, const Board &board) const = 0; 
//     // Pure virtual method to check if a move is valid
//     virtual ~Piece() = default;
//     virtual char getSymbol() const = 0;

//     // added for player classes:
//     bool canPromote(string coord); // determines whether piece can be promoted

// };

// #endif


#ifndef PIECE_H
#define PIECE_H




#include <string>
#include <memory> // For std::unique_ptr
#include <memory> // For std::unique_ptr
#include "board.h"



class Piece {
protected:
   bool white;
   char symbol;
public:
   Piece(bool isWhite, char symbol); // Constructor
   virtual bool isValidMove(const std::string &from, const std::string &to, const std::unique_ptr<Board> &board) const = 0; // Pure virtual method
   virtual ~Piece() = default;
   virtual char getSymbol() const = 0;
   bool isWhite() const { return white; }
};


#endif // PIECE_H



protected:
   bool white;
   char symbol;
public:
   Piece(bool isWhite, char symbol); // Constructor
   virtual bool isValidMove(const std::string &from, const std::string &to, const std::unique_ptr<Board> &board) const = 0; // Pure virtual method
   virtual ~Piece() = default;
   virtual char getSymbol() const = 0;
   bool isWhite() const { return white; }
};


#endif // PIECE_H
