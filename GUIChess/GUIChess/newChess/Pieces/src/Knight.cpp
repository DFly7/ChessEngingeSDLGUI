//
//  Knight.cpp
//  newChess
//
//  Created by Darragh Flynn on 10/09/2024.
//

#include "Knight.hpp"
#include <stdio.h>


Knight::Knight(int c): Piece(c){}

char Knight::getType() const{
    return(color == 1) ? 'N' : 'n';
}

int Knight::getValue() const{
    return 3;
}

Knight* Knight::clone() const { return new Knight(*this); }

Knight::~Knight()  {
    std::cout << "Knight destructor called" << std::endl;
}

std::vector<Move> Knight::GenMoves(Piece* Board[8][8], int r, int c) const{
    std::vector<Move> legalMoves;
    
    std::pair<int, int> offSet[] = { {2, -1}, {2, 1}, {-2, 1}, {-2, -1}, {1,-2}, {1,2},{-1,2}, {-1,-2} };
    
//    { {2, -1}, {2, 1}, {-2, 1}, {-2, -1}, {1,-2}, {1,2},{-1,2}, {-1,-2} }
    for(std::pair<int,int> offS: offSet){
        if(isOnBoard(r+offS.first, c+offS.second) and (Board[r+offS.first][c+offS.second] == nullptr or Board[r+offS.first][c+offS.second]->getColor() != getColor())){
            Move move{getType(),r,c,r+offS.first,c+offS.second};
            legalMoves.emplace_back(move);
        }
    }
    return legalMoves;
}

