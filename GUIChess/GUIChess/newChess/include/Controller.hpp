//
//  Controller.hpp
//  newChess
//
//  Created by Darragh Flynn on 10/09/2024.
//

#ifndef Controller_hpp
#define Controller_hpp

#include <stdio.h>
#include "Model.hpp"
#include "../Pieces/include/Piece.hpp"

class Controller{
    //   pass in model
    Model* model1;
public:
    Controller();
    void setModel(Model* model);
    void gameLoop();
    bool Makemove(int startRow, int startCol, int endRow, int endCol, int player);
    bool validateMove(Move move);
    std::vector<Move> generateLegalMoves(Piece* board[8][8], int player);
    void makeAIMove();
    bool kingInCheck();
    std::vector<Move> getLegalCheckMoves(Piece* board[8][8]);
    bool checkMate();
    int eval(Piece* board[8][8]);
    int miniMax(Piece* board[8][8], int depth, bool maxPlayer, Move*& best);
    
    void deleteBoard(Piece* board[8][8]);
    void deepCopyBoard(Piece* board[8][8], Piece* newBoard[8][8]);
    void SimMakeMove(Piece* board[8][8], Move move);
    void printBoard(Piece* board[8][8]);


    };

#endif /* Controller_hpp */
