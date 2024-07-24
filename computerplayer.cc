
#include "player.h"
#include <limits>
// for INT_MAX/MIN, max(), min()


#include "computerplayer.h"
using namespace std;


ComputerPlayer::ComputerPlayer(int level, bool isWhite) : level{level}, isWhite{isWhite}, Player{isWhite} {}

string ComputerPlayer::level1(Board *board, bool isWhite) {
    // random moves
    map<string, char> piecesLeft = (*board).pieceCoords(isWhite);

    // find from coord
    auto it = piecesLeft.begin();
    advance(it, rand() % piecesLeft.size());
    // take random from piecesLeft

    // int index = (rand() % piecesLeft.size());
    // map<string, char> from = piecesLeft[index];

    string fromCoord = it->first; 
    Piece* piece = (*board).getPiece(fromCoord);


    map<string, int> possibleMoves = (*board).possibleMoves(fromCoord);
    auto jt = possibleMoves.begin();
    advance(jt, rand() % possibleMoves.size());
    // take random move
    // map<string, int> move = possibleMoves[index];
    string toCoord = jt->first;

    /*
    // string index = (rand() % possibleMoves.size())->first;
    // find to coord
    // auto jt = move.begin();
    // advance(it, rand() %  move.size());
    */

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
    map<map<string, char>, map<string, int>> allMovesOpp = (*board).allMoves(isWhite);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

int evaluateBoard(Board *board, bool isWhite) {
    if ((*board).isInCheckmate(isWhite)) {
        return isWhite ? -9999 : 9999;
        // replace with <limits> int min max
    } else if ((*board).isStalemate(isWhite)) {
        return 0;
    }

    map<char, int> values = {
        {'p', 1}, {'P', 1},
        {'k', 3}, {'K', 3},
        {'b', 3}, {'B', 3},
        {'r', 5}, {'R', 5},
        {'q', 9}, {'Q', 9}
    };

    // map<string, char> pieceCoords(bool isWhite);

    map<string, char> pieceWhite = (*board).pieceCoords(isWhite);
    map<string, char> pieceBlack = (*board).pieceCoords(!isWhite);

    int i = 0;
    int evaluated = 0;
    map<string, char> piece;
    auto it = pieceWhite.begin();

    for (it = pieceWhite.begin(); it != pieceWhite.end(); ++it) {
        evaluated += it->second;
    }

    for (it = pieceBlack.begin(); it != pieceBlack.end(); ++it) {
        evaluated -= it->second;
    }

    return evaluated;
}

int miniMax(Board *board, int depth, int alpha, int beta, bool isMaxPlayer, bool isWhite) {
    if (depth == 0 || (*board).isStalemate() 
        || (*board).isInCheckmate(isWhite) || (*board).isInCheckmate(!isWhite)) {
        return evaluateBoard(board, isWhite);
    }

    map<map<string, char>, map<string, int>> allMovesWhite = (*board).allMoves(isWhite);
    map<map<string, char>, map<string, int>> allMovesBlack = (*board).allMoves(!isWhite);

    // combine into one map
    map<map<string, char>, map<string, int>> allMoves;
    allMoves.insert(allMovesWhite.begin(), allMovesWhite.end());
    allMoves.insert(allMovesBlack.begin(), allMovesBlack.end());
    //

    auto it = allMoves.begin();

    if (isMaxPlayer) {
        int maxEval = numeric_limits<int>::min();
        for (it = allMoves.begin(); it != allMoves.end(); ++it) {
            const string move = allMoves->first.first + allMoves->second.second;

            (*board).makeAMove(move);
            int eval = miniMax(board, depth - 1, alpha, beta, false, isWhite);
            (*board).undoMove(move);

            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);

            if (beta <= alpha) {
                break;
            }
        }
        return maxEval;
    } else {
        int minEval = numeric_limits<int>::max();
        for (it = allMoves.begin(); it != allMoves.end(); ++it) {
            const string move = allMoves->first.first + allMoves->second.second;
            (*board).makeAMove(move);
            int eval = miniMax(board, depth - 1, alpha, beta, true, isWhite);
            (*board).undoMove(move);
            minEval = min(minEval, eval);
            beta = min(beta, eval);


            if (beta <= alpha) {
                break;
            }
        }
        return minEval;
    }

}

string ComputerPlayer::level4(Board *board, bool isWhite, int depth) {
    // use alpha beta algorithm

    //map<map<string, char>, map<string, int>> allMoves(bool isWhite);
    // <from, symbol>, <to, rank>

    string bestMove;
    int bestValue = numeric_limits<int>::min();
    int alpha = numeric_limits<int>::min();
    int beta = numeric_limits<int>::max();

    // get legal moves
    map<map<string, char>, map<string, int>> allMovesWhite = (*board).allMoves(isWhite);
    map<map<string, char>, map<string, int>> allMovesBlack = (*board).allMoves(!isWhite);

    // combine into one map
    map<map<string, char>, map<string, int>> allMoves;
    allMoves.insert(allMovesWhite.begin(), allMovesWhite.end());
    allMoves.insert(allMovesBlack.begin(), allMovesBlack.end());
    //

    auto it = allMoves.begin();
    int boardValue;

    for (it = allMoves.begin(); it != allMoves.end(); ++it) {
        const string move = allMoves->first.first + allMoves->second.second;
        (*board).makeAMove(move);
        boardValue = miniMax(board, depth - 1, alpha, beta, false, isWhite);
        (*board).undoMove(move);

        if (boardValue > bestValue) {
            bestValue = boardValue;
            bestMove = move;
        }
    }

    return bestMove;

}


string ComputerPlayer::makeMove(Board *board, const string &from, const string &to, const string &promotion) {
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
            int depth = 0;
            return level4(board, isWhite, depth);
            break;
    }

    return "";
}











