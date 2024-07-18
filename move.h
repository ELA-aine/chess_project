#ifndef MOVE_H
#define MOVE_H

#include <string>

class Move {
public:
    Move(const std::string &from, const std::string &to, const std::string &promotion = "");  // Constructor: Initializes a move with start, end positions and optional promotion
    std::string getFrom() const;  // Returns the starting position of the move
    std::string getTo() const;  // Returns the ending position of the move
    std::string getPromotion() const;  // Returns the promotion type if any

private:
    std::string from;  // Starting position
    std::string to;  // Ending position
    std::string promotion;  // Optional promotion type (e.g., "queen")
};

#endif // MOVE_H
