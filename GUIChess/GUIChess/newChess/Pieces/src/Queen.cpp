//
//  Queen.cpp
//  newChess
//
//  Created by Darragh Flynn on 10/09/2024.
//

#include "Queen.hpp"
#include <stdio.h>


Queen::Queen(int c): Piece(c){}

char Queen::getType() const{
    return(color == 1) ? 'Q' : 'q';
}

int Queen::getValue() const{
    return 10;
}


std::vector<Move> Queen::GenMoves(Piece* Board[8][8], int r, int c) const{
    std::vector<Move> legalMoves;
    
    std::vector<Move> Plane;
    std::vector<Move> Diagonal;

    
    Plane = GetPlane(Board, r, c);
    Diagonal = GetDiagonal(Board, r, c);

    legalMoves.insert(legalMoves.end(), Plane.begin(), Plane.end());
    legalMoves.insert(legalMoves.end(), Diagonal.begin(), Diagonal.end());

    return legalMoves;
}

std::vector<Move> Queen::GetDiagonal(Piece* Board[8][8], int r, int c) const{
    std::vector<Move> legalMoves;
    
    std::pair<int, int> offSet[] = { {-1,1}, {-1,-1}, {1,1}, {1,-1} };
    for(std::pair<int,int> offS: offSet){
        int newR = r+offS.first, newC = c+offS.second;
        while (isOnBoard(newR, newC) and Board[newR][newC] == nullptr) {
            
            Move move{getType(),r,c,newR,newC};
            legalMoves.emplace_back(move);
            
            newR = newR + offS.first;
            newC = newC + offS.second;
        }
        if(isOnBoard(newR, newC) and Board[newR][newC] != nullptr and Board[newR][newC]->getColor() != getColor()){
            Move move{getType(),r,c,newR,newC};
            legalMoves.emplace_back(move);
        }
    }
    
    return legalMoves;
}


std::vector<Move> Queen::GetPlane(Piece* Board[8][8], int r, int c) const{
    std::vector<Move> legalMoves;
    
    std::pair<int, int> offSet[] = { {1,0}, {-1,0}, {0,1}, {0,-1} };
    
    for(std::pair<int,int> offS: offSet){
        int newR = r+offS.first, newC = c+offS.second;
        while (isOnBoard(newR, newC) and Board[newR][newC] == nullptr) {
            
            Move move{getType(),r,c,newR,newC};
            legalMoves.emplace_back(move);
            
            newR = newR + offS.first;
            newC = newC + offS.second;
        }
        if(isOnBoard(newR, newC) and Board[newR][newC] != nullptr and Board[newR][newC]->getColor() != getColor()){
            Move move{getType(),r,c,newR,newC};
            legalMoves.emplace_back(move);
        }
    }


    return legalMoves;
}
