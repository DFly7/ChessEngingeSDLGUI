//
//  View.cpp
//  GUIChess
//
//  Created by Darragh Flynn on 11/09/2024.
//

#include "View.hpp"

View::View(Model* model, Controller* controller){
    this->model = model;
    this->controller = controller;
    window = nullptr;
    renderer = nullptr;
    quit = false;
}

View::~View() {
    cleanup();
}

bool View::init(){

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    
    //Create window
    window = SDL_CreateWindow( "ChessBoard", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL ){
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        return false;
    }
    
    textureMan = new TextureManager(renderer);

    bool a = textureMan->loadTexture('p', "BPawn.jpeg");
    bool b = textureMan->loadTexture('b', "BBishop.png");
    bool c = textureMan->loadTexture('k', "BKing.jpeg");
    bool d = textureMan->loadTexture('n', "BKnight.jpeg");
    bool e = textureMan->loadTexture('q', "BQueen.jpeg");
    bool f = textureMan->loadTexture('r', "BRook.jpeg");
    
    bool a1 = textureMan->loadTexture('P', "WPawn.jpeg");
    bool b1 = textureMan->loadTexture('B', "WBishop.jpeg");
    bool c1 = textureMan->loadTexture('K', "WKing.jpeg");
    bool d1 = textureMan->loadTexture('N', "WKnight.jpeg");
    bool e1 = textureMan->loadTexture('Q', "WQueen.jpeg");
    bool f1 = textureMan->loadTexture('R', "WRook.jpeg");

//    /Users/darraghflynn/Documents/Projects/CPP/GUIChess/GUIChess/newChess/Images/BBishop.png
    
    return a and b and c and d and e and f and a1 and b1 and c1 and d1 and e1 and f1;
}

    
void View::run() {
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else {
                handleEvents(e);
            }
        }
        if(model->getPlayer() == model->AIplayer){
            controller->makeAIMove();
        }
        render();
        SDL_Delay(100);
    }
}

void View::render() {
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Render board and pieces
     renderBoard();
     renderPieces();
    
    if(isCLick){
        renderSelect(clickedX, clickedY);
    }

    // Update screen
    SDL_RenderPresent(renderer);
}

void View::renderPieces(){

    for(int j=7; j>=0; j--){
        for(int i=0; i<8; i++){
            if(model->board[j][i] == nullptr){
                continue;
            }
            char pieceId = model->board[j][i]->getType(); // Example: "white_pawn", "black_pawn"
            
            SDL_Rect destRect = { (i*TILE_SIZE), ((7-j) * TILE_SIZE), TILE_SIZE, TILE_SIZE };
            SDL_RenderCopy(renderer, textureMan->getTexture(pieceId), nullptr, &destRect);
        }
    } 
}

void View::renderBoard(){
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            SDL_Color color = ((row + col) % 2 == 0) ? SDL_Color{255, 255, 255, 255} : SDL_Color{0, 0, 0, 255};
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_Rect tileRect = {row * TILE_SIZE, col * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            SDL_RenderFillRect(renderer, &tileRect);
        }
    }
}

void View::renderSelect(int x, int y){
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    
    // Draw a transparent blue square
    SDL_Rect fillRect = { x*TILE_SIZE, y*TILE_SIZE, TILE_SIZE, TILE_SIZE }; // x, y, width, height
    SDL_SetRenderDrawColor(renderer, 100, 149, 237, 128); // Blue color with 50% transparency
    SDL_RenderFillRect(renderer, &fillRect);
}


void View::cleanup() {
    
    textureMan->~TextureManager();
    free(textureMan);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void View::handleEvents(SDL_Event& e){
    if (e.type == SDL_MOUSEBUTTONDOWN){
        printf("down");
        int x, y;
        SDL_GetMouseState(&x, &y);
        std::cout << "Mouse clicked at: (" << (7-y/TILE_SIZE) << ", " << (x/TILE_SIZE) << ")" << std::endl;
        if(isCLick){
            isCLick = !isCLick;
            endX = x/TILE_SIZE;
            endY = y/TILE_SIZE;
            controller->Makemove(7-clickedY,clickedX, 7-endY, endX, model->getPlayer());
        }
        else{
            isCLick = !isCLick;
            clickedX = x/TILE_SIZE;
            clickedY = y/TILE_SIZE;
        }

    }
    if (e.type == SDL_MOUSEBUTTONUP){
        printf("up");
    }
}
