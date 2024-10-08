//
//  Rook.cpp
//  newChess
//
//  Created by Darragh Flynn on 10/09/2024.
//

#include "Rook.hpp"


Rook::Rook(int c): Queen(c){}

char Rook::getType() const{
    return(color == 1) ? 'R' : 'r';
}

int Rook::getValue() const{
    return 5;
}

Rook* Rook::clone() const { return new Rook(*this); }

Rook::~Rook()  {
    std::cout << "Rook destructor called" << std::endl;
}

std::vector<Move> Rook::GenMoves(Piece* Board[8][8], int r, int c) const{
    std::vector<Move> legalMoves;
    
    legalMoves = GetPlane(Board, r, c);
    
    return legalMoves;
}
