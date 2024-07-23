#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include "player.h"


#include "computerplayer.h"


// ComputerPlayer::ComputerPlayer(int level, bool isWhite) : level{level}, isWhite{isWhite}, Player{isWhite} {

// }

std::string level1(Board board, bool isWhite) {
    // random moves
    map<std::string, char> piecesLeft = board.pieceCoords(isWhite);

    // find from coord
    auto it = piecesLeft.begin();
    std::advance(it, std::rand() % piecesLeft.size());

    string fromCoord = it->first;
    Piece* piece = board.getPiece(fromCoord);
    map<string, string> possibleMoves = board.possibleMoves(fromCoord, piece);

    // string index = (std::rand() % possibleMoves.size())->first;
    // find to coord
    auto jt = possibleMoves.begin();
    std::advance(it, std::rand() %  possibleMoves.size());
    std::string toCoord = jt->first;

    // random promotion
    std::string promotionPossibilities[4] = {"queen", "rook", "knight", "bishop"};
    int index = (std::rand() % promotionPossibilities->length());
    std::string promotion = promotionPossibilities[index];

    return fromCoord + toCoord + promotion;

}




std::string level2() {
    // prefers capturing moves and checks over other moves
    





}

std::string level3() {
    // prefers avoiding capture, capturing moves, and checks



}

std::string level4() {




}


std::string ComputerPlayer::makeMove(Board *board) override {
    switch(level) {
        case 1:
            return level1(*board, isWhite);
            break;
        case 2:
            return level2();
            break;
        case 3:
            return level3();
            break;
        case 4:
            return level4();
            break;
    }

    return "";
}













#endif