//
//  Bishop.cpp
//  newChess
//
//  Created by Darragh Flynn on 10/09/2024.
//

#include "Bishop.hpp"

Bishop::Bishop(int c): Queen(c){}

char Bishop::getType() const{
    return(color == 1) ? 'B' : 'b';
}

int Bishop::getValue() const{
    return 3;
}

Bishop::~Bishop()  {
    std::cout << "Bishop destructor called" << std::endl;
}

Bishop* Bishop::clone() const { return new Bishop(*this); }


std::vector<Move> Bishop::GenMoves(Piece* Board[8][8], int r, int c) const{
    std::vector<Move> legalMoves;
    
    legalMoves = GetDiagonal(Board, r, c);
    
    return legalMoves;
}
