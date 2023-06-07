#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include <SDL2/SDL.h>
#include <sol/sol.hpp>
#include <memory>

class LevelLoader {
    public:
        LevelLoader();
        ~LevelLoader();
        void LoadLevel(sol::state& lua, std::shared_ptr<Registry> registry, const std::shared_ptr<AssetStore>& assetStore, SDL_Renderer* renderer, int level);
};

#endif