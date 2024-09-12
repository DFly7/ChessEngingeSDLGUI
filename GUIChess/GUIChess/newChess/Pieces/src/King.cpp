//
//  King.cpp
//  newChess
//
//  Created by Darragh Flynn on 10/09/2024.
//

#include "King.hpp"


King::King(int c): Piece(c){}

char King::getType() const{
    return(color == 1) ? 'K' : 'k';
}

int King::getValue() const{
    return 1000;
}

King* King::clone() const { return new King(*this); }

King::~King()  {
    std::cout << "King destructor called" << std::endl;
}

std::vector<Move> King::GenMoves(Piece* Board[8][8], int r, int c) const{
    std::vector<Move> legalMoves;
    
    std::pair<int, int> offSet[] = { {1,0}, {-1,0}, {0,1}, {0,-1}, {1,1}, {1,-1}, {-1,1}, {-1,-1} };
    char t = getType();

    for(std::pair<int,int> offS: offSet){
        if(isOnBoard(r+offS.first, c+offS.second) and (Board[r+offS.first][c+offS.second] == nullptr or Board[r+offS.first][c+offS.second]->getColor() != getColor())){
            Move move{t,r,c,r+offS.first,c+offS.second};
            legalMoves.emplace_back(move);
        }
    }
    
    return legalMoves;
}
