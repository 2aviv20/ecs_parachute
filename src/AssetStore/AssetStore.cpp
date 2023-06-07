#include "./AssetStore.h"
#include "../Logger/Logger.h"
#include <SDL2/SDL_image.h>
#include "../Animation/Animation.h"

AssetStore::AssetStore() {
    Logger::Log("AssetStore constructor called!");
}

AssetStore::~AssetStore() {
    ClearAssets();
    Logger::Log("AssetStore destructor called!");
}

void AssetStore::ClearAssets() {
    for (auto texture: textures) {
        SDL_DestroyTexture(texture.second);
    }
    textures.clear();

    for (auto font: fonts) {
        TTF_CloseFont(font.second);
    }
    fonts.clear();
    animations.clear();
}

void AssetStore::AddTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filePath) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // Add the texture to the map
    textures.emplace(assetId, texture);

    Logger::Log("Texture added to the AssetStore with id " + assetId);
}

SDL_Texture* AssetStore::GetTexture(const std::string& assetId) {
    return textures[assetId];
}

void AssetStore::AddFont(const std::string& assetId, const std::string& filePath, int fontSize) {
    fonts.emplace(assetId, TTF_OpenFont(filePath.c_str(), fontSize));
}

TTF_Font* AssetStore::GetFont(const std::string& assetId) {
    return fonts[assetId];
}

void AssetStore::AddAnimation(std::string textureId,int num_frames,int speed_rate,bool horizontal,int height, int width){
    Animation animationObject = {.num_frames = num_frames, .speed_rate = speed_rate,.horizontal = horizontal, .width = width, .height = height};
    AssetStore::animations.emplace(textureId, animationObject);
}

Animation AssetStore::GetAnimation(std::string textureId){
    return AssetStore::animations[textureId];
}
