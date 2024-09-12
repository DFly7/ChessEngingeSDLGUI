//
//  Controller.cpp
//  newChess
//
//  Created by Darragh Flynn on 10/09/2024.
//

#include "Controller.hpp"

#include <unordered_map>
#include <vector>
#include <iostream>

#include <limits> // For std::numeric_limits


#include <random>



Controller::Controller(){
    model1 = NULL;
}
    
void Controller::setModel(Model* model){
    this->model1 = model;
}
    
void Controller::gameLoop(){
    while(model1->getFinished() == false){
        char name[6];
        int player = model1->getPlayer();
        model1->printBoard(player);

        printf("%d to play, Enter Move: ", player);
        scanf("%s", name);

        printf("You entered %s\n",name);
        
//        if(Makemove(name, player) == false){
//            printf("Invalid Move\n");
//            continue;
//        }
    }
};


bool Controller::Makemove(int startRow, int startCol, int endRow, int endCol, int player){
        
    if(startRow > 7 or startRow < 0 or startCol > 7 or startCol < 0){
        printf("Invalid Because off boared");
        return false;
    }
    if(model1->board[startRow][startCol] == nullptr){
        printf("Invalid Because Not a piece");
        return false;
    }
    if(model1->board[startRow][startCol]->getColor() != player){
        printf("Invalid Because Not right Player");
        return false;
    }
    
    char type = model1->board[startRow][startCol]->getType();
    printf("type CC:%c", type);

    Move move = {type, startRow, startCol, endRow, endCol};

    if(validateMove(move) == false){
        printf("Invalid Because Not in list");
        return false;
    }
    
    printf("Start Row %d, Start Col %d, End Row %d, End Col %d \n", move.startR, move.startC, move.endR, move.endC);
    
    model1->InputMove(move);
    
    if(checkMate()){
        model1->setFinished(true);
    }
    
    return true;
}

bool Controller::checkMate(){
    return false;
}

bool Controller::validateMove(Move move){
    std::vector<Move> legalMoves;

//    if(kingInCheck()){
//        printf("KING IN CHECK");
//        legalMoves = getLegalCheckMoves(model1->board);
//        
//        for (Move m : legalMoves) {
//            if(m.endR == move.endR and m.endC == move.endC){
//                return true;
//            }
//        }
//        return false;
//    }

    legalMoves = model1->board[move.startR][move.startC]->GenMoves(model1->board, move.startR, move.startC);

    for (Move m : legalMoves) {
        if(m.endR == move.endR and m.endC == move.endC){
            return true;
        }
    }
    return false;
};




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

void Controller::makeAIMove(){
    Move *best = nullptr;
    miniMax(model1->board, 3, false, best);
    
    if (best != nullptr){
        printf("HEREEEE move %c, %d, %d, %d, %d\n", best->name, best->startR, best->startC,best->endR, best->endC);
    }
    
    Move input;
    input.name = best->name;
    input.startR = best->startR;
    input.startC = best->startC;
    input.endR = best->endR;
    input.endC = best->endC;
    
    printf("HEREEEE move %c, %d, %d, %d, %d\n", input.name,input.startR,input.startC,input.endR,input.endC);

    
    model1->InputMove(input);
};


//Random Move
//Move Controller::makeAIMove(){
//    Move move;
//    std::vector<Move> legalMoves;
//
//    legalMoves = generateLegalMoves(model1->board, model1->getPlayer());
//
//    std::random_device rd;  // Obtain a random number from hardware
//    std::mt19937 gen(rd()); // Seed the generator
//
//    std::uniform_int_distribution<int> dis(0, static_cast<int>(legalMoves.size() - 1)); // Define the range
//
//    // Generate a random index
//    size_t index = dis(gen);
//
//    // Return the random element from the vector
//    if(legalMoves.empty()){
//        printf("Legal Moves is EMpty");
//        
//        return move;
//    }
////    validateMove(legalMoves[index]);
//    model1->InputMove(legalMoves[index]);
//    return legalMoves[index];
//}


bool Controller::kingInCheck(){
    std::vector<Move> legalMoves;


    int curPlayer = model1->getPlayer();

    Position* king = (curPlayer == 1) ? model1->Wking : model1->Bking;
    int opponent = (curPlayer == 1) ? 2 : 1;
    printf("CUrr player %d, Op %d", curPlayer, opponent);


    legalMoves = generateLegalMoves(model1->board, opponent);

    printf("KING R%d:C%d", king->r, king->c);

    for (Move m : legalMoves) {
        if(m.endR == king->r and m.endC == king->c){
            printf("BY %c", m.name);
            return true;
        }
    }
    return false;
}

//std::vector<Move> Controller::getLegalCheckMoves(Piece* board[8][8]){
//
//}

int Controller::eval(Piece* board[8][8]){
    int ev = 0;
    
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(board[i][j] == nullptr){
                continue;
            }
            int pieceVal = board[i][j]->getValue();
            int val = (board[i][j]->getColor() == 1) ? pieceVal : -pieceVal;
            ev = ev + val;
        }
    }
    printf("EVAL %d\n", ev);
    return ev;
}

int Controller::miniMax(Piece* board[8][8], int depth, bool maximise, Move*& best){
    if(depth == 0){
        return eval(board);
    }
    
    if(maximise){
        Move* bestMove = nullptr;

        std::vector<Move> legalMoves;
        legalMoves = generateLegalMoves(board, 1);
        
        int maxEval = std::numeric_limits<int>::min();
        int outEV;
        for (Move m : legalMoves) {
            Piece* newBoared[8][8];
            deepCopyBoard(board, newBoared);
            SimMakeMove(newBoared, m);
            printBoard(newBoared);
            outEV = miniMax(newBoared, depth-1, false, best);
            if(outEV>maxEval){
                maxEval = outEV;
                if(bestMove){
                    delete(bestMove);
                }
                bestMove = new Move();
                bestMove->name = m.name;
                bestMove->startR = m.startR;
                bestMove->startC = m.startC;
                bestMove->endR = m.endR;
                bestMove->endC = m.endC;
                
                best = bestMove;
            }
        }
        return maxEval;
    }
    else{
        Move* bestMove = nullptr;

        std::vector<Move> legalMoves;
        legalMoves = generateLegalMoves(board, 2);
        
        int minEval = std::numeric_limits<int>::max();
        
        int outEV;
        for(Move m : legalMoves) {
            Piece* newBoared[8][8];
            deepCopyBoard(board, newBoared);
            SimMakeMove(newBoared, m);
            printBoard(newBoared);
            outEV = miniMax(newBoared, depth-1, true, best);
            if(outEV<minEval){
                minEval = outEV;
                if(bestMove){
                    delete(bestMove);
                }
                bestMove = new Move();
                bestMove->name = m.name;
                bestMove->startR = m.startR;
                bestMove->startC = m.startC;
                bestMove->endR = m.endR;
                bestMove->endC = m.endC;
                
                best = bestMove;
            }
        }
        return minEval;
    }
}

//        if(outEV<ev){
//            printf("LESS\n");
//            ev = outEV;
//            printf("Move %c,%d,%d\n",m.name,m.endR,m.endC);
//            if(bestMove){
//                delete(bestMove);
//            }
//            bestMove = new Move();
//            bestMove->name = m.name;
//            bestMove->startR = m.startR;
//            bestMove->startC = m.startC;
//            bestMove->endR = m.endR;
//            bestMove->endC = m.endC;
//        }
//    }
//    best = bestMove;
//    return 1;

//CHAT GPT TALKING ABOUT AN UNDO MOVE
//
//#include <iostream>
//#include <vector>
//#include <limits> // For std::numeric_limits
//
//// Example Move class
//class Move {
//public:
//    int row, col; // Coordinates of the move
//    Move(int r, int c) : row(r), col(c) {}
//};
//
//// Example Piece class
//class Piece {
//    // Implement your Piece class here
//};
//
//// Evaluate function: this should be implemented based on your game's rules
//int eval(Piece* board[8][8]) {
//    // Return a heuristic evaluation of the board
//    return 0; // Placeholder
//}
//
//// Check if the game is in a terminal state (e.g., checkmate, stalemate)
//bool isTerminalNode(Piece* board[8][8]) {
//    // Implement the check based on your game
//    return false; // Placeholder
//}
//
//// Generate all legal moves for the current player
//std::vector<Move> generateLegalMoves(Piece* board[8][8]) {
//    std::vector<Move> moves;
//    // Implement move generation logic
//    return moves; // Placeholder
//}
//
//// Apply a move to the board
//void makeMove(Piece* board[8][8], const Move& move) {
//    // Implement move application
//}
//
//// Undo a move on the board
//void undoMove(Piece* board[8][8], const Move& move) {
//    // Implement move undo
//}
//
//// Minimax algorithm
//int minimax(Piece* board[8][8], int depth, bool maximizingPlayer) {
//    if (depth == 0 || isTerminalNode(board)) {
//        return eval(board);
//    }
//
//    if (maximizingPlayer) {
//        int maxEval = std::numeric_limits<int>::min();
//        std::vector<Move> legalMoves = generateLegalMoves(board);
//        for (const Move& move : legalMoves) {
//            makeMove(board, move);
//            int eval = minimax(board, depth - 1, false);
//            undoMove(board, move);
//            maxEval = std::max(maxEval, eval);
//        }
//        return maxEval;
//    } else {
//        int minEval = std::numeric_limits<int>::max();
//        std::vector<Move> legalMoves = generateLegalMoves(board);
//        for (const Move& move : legalMoves) {
//            makeMove(board, move);
//            int eval = minimax(board, depth - 1, true);
//            undoMove(board, move);
//            minEval = std::min(minEval, eval);
//        }
//        return minEval;
//    }
//}

// Function to find the best move for the current player
//Move findBestMove(Piece* board[8][8], int depth) {
//    int bestValue = std::numeric_limits<int>::min();
//    Move bestMove(0, 0); // Initialize with default move
//
//    std::vector<Move> legalMoves = generateLegalMoves(board);
//    for (const Move& move : legalMoves) {
//        makeMove(board, move);
//        int moveValue = minimax(board, depth - 1, false);
//        undoMove(board, move);
//
//        if (moveValue > bestValue) {
//            bestValue = moveValue;
//            bestMove = move;
//        }
//    }
//    return bestMove;
//}
//
//int main() {
//    Piece* board[8][8] = {}; // Initialize the board
//    int depth = 3; // Search depth
//
//    Move bestMove = findBestMove(board, depth);
//    std::cout << "Best Move: (" << bestMove.row << ", " << bestMove.col << ")\n";
//
//    return 0;
//}
//

//
//int Controller::miniMax(Piece* board[8][8], int depth, bool maximise, Move*& best){
//    std::vector<Move> legalMoves;
//    
//    Move* bestMove = nullptr;
//    
//    legalMoves = generateLegalMoves(board, 2);
//    int ev = 100;
//    int outEV;
//    for (Move m : legalMoves) {
//        Piece* newBoared[8][8];
//        deepCopyBoard(board, newBoared);
//        SimMakeMove(newBoared, m);
//        printBoard(newBoared);
//        outEV = eval(newBoared);
//        if(outEV<ev){
//            printf("LESS\n");
//            ev = outEV;
//            printf("Move %c,%d,%d\n",m.name,m.endR,m.endC);
//            if(bestMove){
//                delete(bestMove);
//            }
//            bestMove = new Move();
//            bestMove->name = m.name;
//            bestMove->startR = m.startR;
//            bestMove->startC = m.startC;
//            bestMove->endR = m.endR;
//            bestMove->endC = m.endC;
//        }
//    }
//    best = bestMove;
//    return 1;
//}

void Controller::deleteBoard(Piece* board[8][8]) {
    // Iterate through each cell in the 2D array
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != nullptr) {
                delete board[i][j]; // Delete the dynamically allocated Piece
            }
        }
    }
}

void Controller::deepCopyBoard(Piece* board[8][8], Piece* newBoard[8][8]) {
    // Allocate memory for the new board

    // Copy each piece from the old board to the new board
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != nullptr) {
                newBoard[i][j] = board[i][j]->clone(); // Clone the piece
            } else {
                newBoard[i][j] = nullptr;
            }
        }
    }
};


void Controller::SimMakeMove(Piece* board[8][8], Move move){
    Piece* temp = board[move.startR][move.startC];
//    printf("type Temp:%c", temp->getType());
    
    board[move.startR][move.startC] = nullptr;
    
    board[move.endR][move.endC] = temp;
}

void Controller::printBoard(Piece* board[8][8]) {
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
    
};
