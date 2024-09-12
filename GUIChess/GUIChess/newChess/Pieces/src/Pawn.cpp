//
//  Pawn.cpp
//  newChess
//
//  Created by Darragh Flynn on 10/09/2024.
//

#include "Pawn.hpp"
#include <stdio.h>

Pawn::Pawn(int c): Piece(c){}

char Pawn::getType() const{
    return(color == 1) ? 'P' : 'p';
}

int Pawn::getValue() const{
    return 1;
}

Pawn* Pawn::clone() const { return new Pawn(*this); }

Pawn::~Pawn()  {
    std::cout << "Pawn destructor called" << std::endl;
}

std::vector<Move> Pawn::GenMoves(Piece* Board[8][8], int r, int c) const{
    std::vector<Move> legalMoves;
    
    int direction = (1 == getColor()) ? 1 : -1;
    int startRow = (1 == getColor()) ? 1 : 6;
    
    char t = getType();
    
    int newRow = r + direction;
    if(isOnBoard(newRow, c) and Board[newRow][c] == nullptr){
        Move move{t,r,c,newRow,c};
        legalMoves.emplace_back(move);
    }
    if(r == startRow and Board[newRow+direction][c] == nullptr){
        Move move{t,r,c,newRow+direction,c};
        legalMoves.emplace_back(move);
    }
    
    if(isOnBoard(newRow, c+1) and Board[newRow][c+1] != nullptr and Board[newRow][c+1]->getColor() != getColor()){
        Move move{t,r,c,newRow,c+1};
        legalMoves.emplace_back(move);
    }
    if(isOnBoard(newRow, c-1) and Board[newRow][c-1] != nullptr and Board[newRow][c-1]->getColor() != getColor()){
        Move move{t,r,c,newRow,c-1};
        legalMoves.emplace_back(move);
    }
    
    return legalMoves;
}
