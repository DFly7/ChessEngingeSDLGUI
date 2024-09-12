//#include <SDL2/SDL.h>
//#include <SDL2_image/SDL_image.h>
//#include <iostream>
//#include <vector>
//#include <string>
//
//const int WINDOW_WIDTH = 640;
//const int WINDOW_HEIGHT = 640;
//const int BOARD_SIZE = 8;
//const int TILE_SIZE = WINDOW_WIDTH / BOARD_SIZE;
//
//bool validateCoords(int startRow, int startCol, int endRow, int endCol){
//    return true;
//}
//
//
//// Structure to store piece information
//struct ChessPiece {
//    SDL_Texture* texture;
//    SDL_Rect destRect; // Position and size on the board
//};
//
//// Function to load texture
//SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer) {
//    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
//    if (!loadedSurface) {
//        std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
//        return nullptr;
//    }
//    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
//    SDL_FreeSurface(loadedSurface);
//    return texture;
//}
//
//// Function to render a piece
//void renderPiece(SDL_Renderer* renderer, const ChessPiece& piece) {
//    SDL_RenderCopy(renderer, piece.texture, nullptr, &piece.destRect);
//}
//
//// Function to render the chessboard
//void renderChessboard(SDL_Renderer* renderer) {
//    for (int row = 0; row < BOARD_SIZE; ++row) {
//        for (int col = 0; col < BOARD_SIZE; ++col) {
//            SDL_Color color = ((row + col) % 2 == 0) ? SDL_Color{255, 255, 255, 255} : SDL_Color{0, 0, 0, 255};
//            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
//            SDL_Rect tileRect = {col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE};
//            SDL_RenderFillRect(renderer, &tileRect);
//        }
//    }
//}
//
//void handleEvents(SDL_Event& e, std::vector<ChessPiece>& pieces, int& startRow, int& startCol, int& endRow, int& endCol, bool& pieceMoved) {
//    static bool isDragging = false;
//    static ChessPiece* selectedPiece = nullptr;
//    static int initialX, initialY;
//    static int initialRow, initialCol;
//    static SDL_Rect originalRect;
//
//    while (SDL_PollEvent(&e) != 0) {
//        if (e.type == SDL_QUIT) {
//            exit(0);
//        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
//            if (e.button.button == SDL_BUTTON_LEFT) {
//                int mouseX = e.button.x;
//                int mouseY = e.button.y;
//
//                // Check if a piece is clicked
//                for (auto& piece : pieces) {
//                    if (mouseX >= piece.destRect.x && mouseX <= piece.destRect.x + piece.destRect.w &&
//                        mouseY >= piece.destRect.y && mouseY <= piece.destRect.y + piece.destRect.h) {
//                        selectedPiece = &piece;
//                        isDragging = true;
//                        initialX = mouseX - piece.destRect.x;
//                        initialY = mouseY - piece.destRect.y;
//                        // Save original position and calculate initial row and column
//                        originalRect = piece.destRect;
//                        initialRow = piece.destRect.y / TILE_SIZE;
//                        initialCol = piece.destRect.x / TILE_SIZE;
//                        startRow = initialRow;
//                        startCol = initialCol;
//                        pieceMoved = false; // Reset piece moved flag
//                        break;
//                    }
//                }
//            }
//        } else if (e.type == SDL_MOUSEBUTTONUP) {
//            if (e.button.button == SDL_BUTTON_LEFT) {
//                if (selectedPiece) {
//                    // Snap to nearest grid
//                    int gridX = (selectedPiece->destRect.x + TILE_SIZE / 2) / TILE_SIZE * TILE_SIZE;
//                    int gridY = (selectedPiece->destRect.y + TILE_SIZE / 2) / TILE_SIZE * TILE_SIZE;
//
//                    endRow = gridY / TILE_SIZE;
//                    endCol = gridX / TILE_SIZE;
//
//                    // Validate the new coordinates with start and end coordinates
//                    if (validateCoords(startRow, startCol, endRow, endCol)) {
//                        // If valid, update the piece position
//                        selectedPiece->destRect.x = gridX;
//                        selectedPiece->destRect.y = gridY;
//                        pieceMoved = true; // Set piece moved flag
//                    } else {
//                        // If invalid, revert to the original position
//                        selectedPiece->destRect = originalRect;
//                        endRow = initialRow;
//                        endCol = initialCol;
//                    }
//
//                    isDragging = false;
//                    selectedPiece = nullptr;
//                }
//            }
//        } else if (e.type == SDL_MOUSEMOTION) {
//            if (isDragging && selectedPiece) {
//                selectedPiece->destRect.x = e.motion.x - initialX;
//                selectedPiece->destRect.y = e.motion.y - initialY;
//            }
//        }
//    }
//}
//
//void renderPieces(SDL_Renderer* renderer, ChessPiece* board[BOARD_SIZE][BOARD_SIZE]) {
//    for (int row = 0; row < BOARD_SIZE; ++row) {
//        for (int col = 0; col < BOARD_SIZE; ++col) {
//            ChessPiece* piece = board[row][col];
//            if (piece) {
//                SDL_Rect destRect = { col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE };
//                SDL_RenderCopy(renderer, piece->texture, NULL, &destRect);
//            }
//        }
//    }
//}
//
//
//int main(int argc, char* argv[]) {
//    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
//        return 1;
//    }
//
//    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
//        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
//        SDL_Quit();
//        return 1;
//    }
//
//    SDL_Window* window = SDL_CreateWindow("Chessboard with Snap", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
//    if (!window) {
//        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
//        IMG_Quit();
//        SDL_Quit();
//        return 1;
//    }
//
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//    if (!renderer) {
//        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
//        SDL_DestroyWindow(window);
//        IMG_Quit();
//        SDL_Quit();
//        return 1;
//    }
//
//    // Load textures for pieces
//    SDL_Texture* pawnTexture = loadTexture("BPawn.jpeg", renderer);
//    SDL_Texture* rookTexture = loadTexture("BPawn.jpeg", renderer);
//    // Add other pieces as needed
//
//    // Create pieces
//    std::vector<ChessPiece> pieces = {
//        {pawnTexture, {0, 0, TILE_SIZE, TILE_SIZE}}, // Example positions
//        {rookTexture, {TILE_SIZE, 0+TILE_SIZE, TILE_SIZE, TILE_SIZE}},
//        {rookTexture, {TILE_SIZE+TILE_SIZE, 0, TILE_SIZE, TILE_SIZE}}
//
//        // Add more pieces with their textures and positions
//    };
//    bool quit = false;
//      SDL_Event e;
//      int startRow, startCol, endRow, endCol;
//      bool pieceMoved = false;
//
//      while (!quit) {
//          handleEvents(e, pieces, startRow, startCol, endRow, endCol, pieceMoved);
//
//          // Clear screen
//          SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//          SDL_RenderClear(renderer);
//
//          // Render the chessboard
//          renderChessboard(renderer);
//
//          // Render pieces
//          for (const auto& piece : pieces) {
//              renderPiece(renderer, piece);
//          }
//
//          // Update screen
//          SDL_RenderPresent(renderer);
//
//          // Handle piece moved event
//          if (pieceMoved) {
//              std::cout << "Piece moved from (" << startRow << ", " << startCol << ") to (" << endRow << ", " << endCol << ")" << std::endl;
//              // Call your controller with startRow, startCol, endRow, endCol
////              yourController.movePiece(startRow, startCol, endRow, endCol);
//              pieceMoved = false; // Reset flag
//          }
//      }
//    // Clean up
//    for (auto& piece : pieces) {
//        SDL_DestroyTexture(piece.texture);
//    }
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    IMG_Quit();
//    SDL_Quit();
//
//    return 0;
//}
//
