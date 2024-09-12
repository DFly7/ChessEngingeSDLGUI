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
    Model* model1 = new Model("rnbqkbnr/ppp1p1pp/3p1p2/8/3B1N2/8/PPPPPPPP/RN1QKB1R");
        
    Controller* control = new Controller();
    control->setModel(model1);
    
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

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
