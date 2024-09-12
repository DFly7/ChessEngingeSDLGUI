//
//  Model.cpp
//  newChess
//
//  Created by Darragh Flynn on 10/09/2024.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <cctype>

#include <memory> // For smart pointers


#include "Model.hpp"


Model::Model(){
        fen = "";
        playerMove = 1;
        isFinished = false;
    }
Model::Model(std::string fen){
        this->fen = fen;
        this->playerMove = 1;
        this->isFinished = false;
        this->AIplayer = 2;
    
    Wking = new Position();
    Wking->r = -1;
    Wking->c = -1;
    
    Bking = new Position();
    Bking->r = -1;
    Bking->c = -1;
    
        initializeBoard();
    }
    
void Model::InputMove(Move move){
    Piece* temp = board[move.startR][move.startC];
    printf("type Temp:%c\n", temp->getType());
    if(temp->getType() == 'k'){
        Bking->r = move.endR;
        Bking->c = move.endC;
    }
    if(temp->getType() == 'K'){
        Wking->r = move.endR;
        Wking->c = move.endC;
    }
    
    board[move.startR][move.startC] = nullptr;
    
    board[move.endR][move.endC] = temp;
    
    playerMove = (playerMove == 1) ? 2 : 1;
    printf("player Move %d\n", playerMove);
}
    
    void Model::setPlayer(int p){
        playerMove = p;
    };
    
    void Model::setFinished(bool f){
        isFinished = f;
    };
    
    int Model::getPlayer(){
        return playerMove;
    }
    
    int Model::getFinished(){
        return isFinished;
    }
    
    void Model::initializeBoard(){
        for(int i=0; i<8; i++){
            for(int j=0; j<8; j++){
                board[i][j] = nullptr;
            };
        };
        
        
        int row = 7;
        int col = 0;
        for(int i=0; i<fen.length(); i++){
            if (fen[i] == '/'){
                row--;
                col = 0;
                continue;
            };
            if (isdigit(fen[i])){
                col = col + (fen[i] - '0');
                continue;
            };
            
            if (isupper(fen[i])){
                if(fen[i] == 'P'){
                    board[row][col] = new Pawn(1);
                }
                else if (fen[i] == 'N'){
                    board[row][col] = new Knight(1);
                }
                else if (fen[i] == 'K'){
                    board[row][col] = new King(1);
                    Wking->r = row;
                    Wking->c = col;
                }
                else if (fen[i] == 'Q'){
                    board[row][col] = new Queen(1);
                }
                else if (fen[i] == 'R'){
                    board[row][col] = new Rook(1);
                }
                else if (fen[i] == 'B'){
                    board[row][col] = new Bishop(1);
                }
            }
            else{
                if(fen[i] == 'p'){
                    board[row][col] = new Pawn(2);
                }
                else if (fen[i] == 'n'){
                    board[row][col] = new Knight(2);
                }
                else if (fen[i] == 'k'){
                    board[row][col] = new King(2);
                    Bking->r = row;
                    Bking->c = col;
                }
                else if (fen[i] == 'q'){
                    board[row][col] = new Queen(2);
                }
                else if (fen[i] == 'r'){
                    board[row][col] = new Rook(2);
                }
                else if (fen[i] == 'b'){
                    board[row][col] = new Bishop(2);
                }
            }
            col += 1;
        }
    };
    
    
    void Model::printBoard(int player) {
        if (player == 1){
            for(int i = 7; i>=0; i--){
                std::cout << i+1 << " ";
                for(int j = 0; j<8; j++){
                    if (board[i][j] == nullptr){
                        std::cout << '0';
                        std::cout << " ";
                        continue;
                    };
                    if (board[i][j]->getColor() == 1) {
                        std::cout << board[i][j]->getType();
                    }
                    else if (board[i][j]->getColor() == 2){
                        std::cout << board[i][j]->getType();
                    }
                    std::cout << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "  ";
            for (int i = 0; i < 8; ++i) {
                std::cout << char('a' + i) << " ";
            }
            std::cout << std::endl;
        }
        else{
            for(int i = 0; i<8; i++){
                std::cout << i+1 << " ";
                for(int j = 7; j>=0; j--){
                    if (board[i][j] == nullptr){
                        std::cout << '0';
                        std::cout << " ";
                        continue;
                    };
                    if (board[i][j]->getColor() == 1) {
                        std::cout << board[i][j]->getType();
                    }
                    else if (board[i][j]->getColor() == 2){
                        std::cout << board[i][j]->getType();
                    }
                    std::cout << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "  ";
            for (int i = 0; i < 8; i++) {
                std::cout << char('h' - i) << " ";
            }
            std::cout << std::endl;
        }
    };
