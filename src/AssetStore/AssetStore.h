#ifndef ASSETSTORE_H
#define ASSETSTORE_H

#include <map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../Animation/Animation.h"

class AssetStore {
    private:
        std::map<std::string, SDL_Texture*> textures;
        std::map<std::string, TTF_Font*> fonts;
        std::map<std::string, Animation> animations;
    public:
        AssetStore();
        ~AssetStore();

        void ClearAssets();

        void AddTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filePath);
        SDL_Texture* GetTexture(const std::string& assetId);

        void AddFont(const std::string& assetId, const std::string& filePath, int fontSize);
        TTF_Font* GetFont(const std::string& assetId);

        void AddAnimation(std::string textureId,int num_frames,int speed_rate,bool horizontal, int width, int height);
        Animation GetAnimation(std::string textureId);
};

#endif
