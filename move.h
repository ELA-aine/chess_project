#ifndef MOVE_H
#define MOVE_H

#include <string>

class Move {
public:
    Move(const std::string &from, const std::string &to, bool isWhite, const std::string &piece, const std::string &capture = "", const std::string &promotion = "");  // Constructor: Initializes a move with start, end positions and optional promotion
    std::string getFrom() const;  // Returns the starting position of the move
    std::string getTo() const;  // Returns the ending position of the move
    std::string getPromotion() const;  // Returns the promotion type if any
    std::string getPiece() const;
    std::string getCapture() const;
    bool getWhite() const;

private:
    std::string from;  // Starting position
    std::string to;  // Ending position
    bool isWhite = true;
    std::string piece;
    std::string capture;
    std::string promotion;  // Optional promotion type (e.g., "queen")
    
};

#endif // MOVE_H
