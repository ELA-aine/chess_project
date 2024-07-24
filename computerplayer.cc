
#include "player.h"


#include "computerplayer.h"
using namespace std;


ComputerPlayer::ComputerPlayer(int level, bool isWhite) : level{level}, isWhite{isWhite}, Player{isWhite} {}

string ComputerPlayer::level1(Board *board, bool isWhite) {
    // random moves
    map<string, char> piecesLeft = (*board).pieceCoords(isWhite);

    // find from coord
    auto it = piecesLeft.begin();
    advance(it, rand() % piecesLeft.size());

    string fromCoord = it->first;
    Piece* piece = (*board).getPiece(fromCoord);
    vector<map<string, int>> possibleMoves = (*board).possibleMoves(fromCoord);


    int index = (rand() % possibleMoves.size());
    map<string, int> move = possibleMoves[index];


    // string index = (rand() % possibleMoves.size())->first;
    // find to coord
    auto jt = move.begin();
    advance(it, rand() %  move.size());
    string toCoord = jt->first;

    string promotion = "";

    // must meet promotion standards
    if ((piece->getSymbol() == 'P' || piece->getSymbol() == 'p') && piece->canPromote(fromCoord)) {
        // random promotion
        string promotionPossibilities[5] = {"queen", "rook", "knight", "bishop", ""};
        // possible pieces to be promoted to
        int index = (rand() % promotionPossibilities->length());
        promotion = promotionPossibilities[index];
    }

    return fromCoord + toCoord + promotion;

}




string ComputerPlayer::level2(Board *board, bool isWhite) {
    // prefers capturing moves and checks over other moves

    // map<map<string, char>, vector<map<string, int>>> allMovesOpp(bool isWhite);

    map<map<string, char>, vector<map<string, int>>> allMoves = (*board).allMoves(isWhite);

    map<int, vector<map<string, string>>> priorityMoves;
    vector<map<string, string>> value2;
    vector<map<string, string>> value3;
    vector<map<string, string>> value4;

    for (auto& pieceMoves : allMoves) {
        // pieceMoves.first : map<string, char>
        // pieceMoves.second : vector<map<string, int>>
        map<string, char> from = pieceMoves.first;
        string piecePosition = from.first; // fix later

        vector<map<string, int>>& toCoords = pieceMoves.second;

        for (auto& fromCoord : toCoords) { // map<string, int>

            for (auto& coord : fromCoord) { 
                // coord.first : from coordinate
                // coord.second : value of move

                map<string, string> move;
                move[piecePosition] = coord.first;

                if (coord.second == 2) { // capture or better 
                    value2.emplace_back(move);
                } else if (coord.second == 3) {
                    value3.emplace_back(move);
                } else if (coord.second == 4) {
                    value4.emplace_back(move);
                }

            }
        }
    }

    priorityMoves[2] = value2;
    priorityMoves[3] = value3;
    priorityMoves[4] = value4;

    string to;
    string from;
    string promotion;
    // find max, if 4, take random 4, ...

    return to + from + promotion;

}

string ComputerPlayer::level3(Board *board, bool isWhite) {
    // prefers avoiding capture, capturing moves, and checks
    
    // same from level2, make helper later
    // take all opponent moves
    map<map<string, char>, vector<map<string, int>>> allMovesOpp = (*board).allMoves(isWhite);

    map<int, vector<map<map<string, string>, char>>> priorityMoves;
    // <move value, <to, from>>
    vector<map<map<string, string>, char>> value2;
    vector<map<map<string, string>, char>> value3;
    vector<map<map<string, string>, char>> value4;

    // get capture and above moves
    for (auto& pieceMoves : allMovesOpp) {
        // pieceMoves.first : map<string, char>
        // pieceMoves.second : vector<map<string, int>>
        map<string, char> from = pieceMoves.first;
        string piecePosition = from.first; // fix later
        char pieceType = from.second;

        vector<map<string, int>>& toCoords = pieceMoves.second;

        for (auto& fromCoord : toCoords) { // map<string, int>

            for (auto& coord : fromCoord) { 
                // coord.first : from coordinate
                // coord.second : value of move

                map<string, string> move;
                move[piecePosition] = coord.first;
                map<map<string, string>, char> pieceMove;
                pieceMove[move] = pieceType;
                
                if (coord.second == 2) { // capture or better 
                    value2.emplace_back(pieceMove);
                } else if (coord.second == 3) {
                    value3.emplace_back(pieceMove);
                } else if (coord.second == 4) {
                    value4.emplace_back(pieceMove);
                }

            }
        }
    }

    priorityMoves[2] = value2;
    priorityMoves[3] = value3;
    priorityMoves[4] = value4;

    // map<int, vector<map<string, string>>> priorityMoves;

    vector<map<string, string>> captureAvoid;

    int i = 0, j = 0, k = 0;

    for (i = 4; i > 1; i--) {
        vector<map<map<string, string>, char>> moves = priorityMoves[i];

        for (j = 0; j < moves.size(); i++) {
            // map<string, int> possibleMoves(string coord, Piece *piece);
            map<map<string, string>, char> coordPiece = moves[j];
            map<string, string> coord = coordPiece.first;
            char pieceType = coordPiece.second;
            string thisFrom = coord.second; // fix later
            vector<map<string, int>> captureAndAvoid = (*board).possibleMoves(thisFrom);

            for (k = 0; k < captureAndAvoid.size(); k++) {
                if (captureAndAvoid[k].second > 1) {
                    map<string, string> possibleMove;
                    possibleMove[thisFrom] = captureAndAvoid[k].first;

                    captureAvoid.emplace_back(possibleMove);
                }

            }


            
        }
    }

    // find max, if 4, take random 4, ...
    // captureAvoid

}

string ComputerPlayer::level4(Board *board, bool isWhite) {
    



}


string ComputerPlayer::makeMove(Board *board, const std::string &from, const std::string &to, const std::string &promotion) {
    switch(level) {
        case 1:
            return level1(board, isWhite);
            break;
        case 2:
            return level2(board, isWhite);
            break;
        case 3:
            return level3(board, isWhite);
            break;
        case 4:
            return level4(board, isWhite);
            break;
    }

    return "";
}











