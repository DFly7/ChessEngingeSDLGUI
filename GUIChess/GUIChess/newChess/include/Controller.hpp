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
    bool Makemove(char name[5], int player);
    bool validateMove(Move move);
    std::vector<Move> GetPieceMoves(int r, int c, int player);
    std::vector<Move> generateLegalMoves(Piece* board[8][8], int player);
    std::vector<Move> PieceMoves(char type, int color);
    Move makeAIMove();
    };

#endif /* Controller_hpp */
