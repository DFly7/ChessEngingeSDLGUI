//
//  main.cpp
//  newChess
//
//  Created by Darragh Flynn on 10/09/2024.
//

#include <iostream>
#include "Pieces/include/Piece.hpp"
#include "Pieces/include/Pawn.hpp"
#include "Pieces/include/Knight.hpp"
#include "Pieces/include/Queen.hpp"

#include "Pieces/include/Rook.hpp"

#include "include/Model.hpp"
#include "include/Controller.hpp"

#include "include/View.hpp"

#include <stdio.h>
#include <filesystem>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    std::cout << "Hello, World!\n";
    std::string start = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    Model* model1 = new Model("r3kbnr/p3pppp/2q5/8/4B3/2N5/PPPPPPPP/R1BQK1NR");
//    "4k3/1r6/7p/2bP4/4P3/1R3P2/P1P2NPP/4KB1R"
    Controller* control = new Controller();
    control->setModel(model1);
    
//    model1->printBoard(1);
//    
//    control->makeAIMove();
//    model1->printBoard(1);


    
//    Move *best = nullptr;
//    control->miniMax(model1->board, 1, true, best);
//    
//    if (best != nullptr){
//        printf("move %c, %d, %d\n", best->name, best->endR, best->endC);
//    }
//    model1->printBoard(1);
//    
//    Move input;
//    input.name = best->name;
//    input.startR = best->startR;
//    input.startC = best->startC;
//    input.endR = best->endR;
//    input.endC = best->endC;
//    
//    model1->InputMove(input);
//    
//    model1->printBoard(1);

    
//    control->gameLoop();
    

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        return 1;
     }
    

    View view = View(model1, control);
    if (!view.init()) {
        return 1; // Initialization failed
    }


    view.run();
    
    return 0;
}
