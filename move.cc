#include "move.h"



Move::Move(const std::string &from, const std::string &to, bool isWhite, const std::string &piece, 
           const std::string &capture = "", const std::string &promotion = "") {}

std::string Move::getFrom() const {
  return from;
}


std::string Move::getTo() const {
  return to;
}


std::string Move::getPromotion() const {
  return promotion;
}

std::string Move::getPiece() const {
  return piece;
}

std::string Move::getCapture() const {
  return capture;
}