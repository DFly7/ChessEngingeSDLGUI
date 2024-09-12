//
//  Controller.cpp
//  newChess
//
//  Created by Darragh Flynn on 10/09/2024.
//

#include "Controller.hpp"



#include <unordered_map>
#include <vector>

#include <random>



Controller::Controller(){
    model1 = NULL;
}
    
void Controller::setModel(Model* model){
    this->model1 = model;
}
    
    void Controller::gameLoop(){
        std::unordered_map<int, int> Map;
        Map[1] = 2;
        Map[2] = 1;

        while(model1->getFinished() == false){
            char name[6];
            int player = model1->getPlayer();
            model1->printBoard(player);

            printf("%d to play, Enter Move: ", player);
            scanf("%s", name);

            printf("You entered %s\n",name);
            
            if(Makemove(name, player) == false){
                printf("Invalid Move\n");
                continue;
            }
            
            model1->setPlayer(Map[player]);
            
        }
    };

    
    bool Controller::Makemove(char name[5], int player){
        Move move;
        
        std::unordered_map<char, int> Map;
        
        Map['a'] = 0;
        Map['b'] = 1;
        Map['c'] = 2;
        Map['d'] = 3;
        Map['e'] = 4;
        Map['f'] = 5;
        Map['g'] = 6;
        Map['h'] = 7;

        move.startR = int(name[1])-1 - '0';
        move.startC = Map[name[0]];
        
        move.endR = int(name[3])-1 - '0';
        move.endC = Map[name[2]];
        
        if(move.startR > 7 or move.startR < 0 or move.startC > 7 or move.startC < 0){
            printf("Invalid Because off boared");
            return false;
        }
        
        if(model1->board[move.startR][move.startC] == nullptr){
            printf("Invalid Because Not a piece");
            return false;
        }
        
        if(model1->board[move.startR][move.startC]->getColor() != player){
            printf("Invalid Because Not right Player");
            return false;
        }
        
        move.name = model1->board[move.startR][move.startC]->getType();
        
        if(validateMove(move) == false){
            printf("Invalid Because Not in list");
            return false;
        }
        
        printf("Start Row %d, Start Col %d, End Row %d, End Col %d \n", move.startR, move.startC, move.endR, move.endC);
        
        
        model1->makeMove(move);
        
        return true;
    }

bool Controller::validateMove(Move move){
    std::vector<Move> legalMoves;
    
    if(move.startR > 7 or move.startR < 0 or move.startC > 7 or move.startC < 0){
        printf("Invalid Because off boared");
        return false;
    }
    
    if(model1->board[move.startR][move.startC] == nullptr){
        printf("Invalid Because Not a piece");
        return false;
    }
    
    if(model1->board[move.startR][move.startC]->getColor() != model1->playerMove){
        printf("Invalid Because Not right Player");
        return false;
    }
    
    legalMoves = model1->board[move.startR][move.startC]->GenMoves(model1->board, move.startR, move.startC);

    for (Move m : legalMoves) {
        if(m.endR == move.endR and m.endC == move.endC){        
            model1->makeMove(move);
            return true;
        }
    }
    return false;
};

std::vector<Move> Controller::GetPieceMoves(int r, int c, int player){
    std::vector<Move> legalMoves;
    
    legalMoves = model1->board[r][c]->GenMoves(model1->board, r, c);
    return legalMoves;
}

std::vector<Move> Controller::generateLegalMoves(Piece* board[8][8], int player) {
    std::vector<Move> legalMoves;

    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            std::vector<Move> legalMovesPiece;
            if(model1->board[i][j] != nullptr and model1->board[i][j]->getColor() == player){
                legalMovesPiece = model1->board[i][j]->GenMoves(board, i, j);
                legalMoves.insert(legalMoves.end(), legalMovesPiece.begin(), legalMovesPiece.end());
            }
        };
    };

    return legalMoves;
}

Move Controller::makeAIMove(){
    Move move;
    std::vector<Move> legalMoves;

    legalMoves = generateLegalMoves(model1->board, model1->getPlayer());
    
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    
    std::uniform_int_distribution<int> dis(0, static_cast<int>(legalMoves.size() - 1)); // Define the range

    // Generate a random index
    size_t index = dis(gen);

    // Return the random element from the vector
    model1->makeMove(legalMoves[index]);
    return legalMoves[index];
}
