//
//  TextureManager.cpp
//  GUIChess
//
//  Created by Darragh Flynn on 11/09/2024.
//

#include "TextureManager.hpp"

TextureManager::TextureManager(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

TextureManager::~TextureManager() {
    for (auto& pair : textures) {
        SDL_DestroyTexture(pair.second);
    }
}

bool TextureManager::loadTexture(char id, const std::string& path) {
    Uint32 colorKey = SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB24), 255, 255, 255);

    std::cerr << path << std::endl;
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cerr << "Unable to load image: " << IMG_GetError() << std::endl;
        return false;
    }
    
    // Apply color keying
    if (SDL_SetColorKey(surface, SDL_TRUE, colorKey) != 0) {
        std::cerr << "Unable to set color key: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return false;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        std::cerr << "Unable to create texture: " << SDL_GetError() << std::endl;
        return false;
    }
    if (SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) != 0) {
        std::cerr << "Unable to set blend mode: " << SDL_GetError() << std::endl;
        return false;
    }
    textures[id] = texture;
    return true;
}

SDL_Texture* TextureManager::getTexture(char id) const {
    auto it = textures.find(id);
    return it != textures.end() ? it->second : nullptr;
}
