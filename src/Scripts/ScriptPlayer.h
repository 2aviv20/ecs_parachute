#ifndef SCRIPT_PLAYER_H
#define SCRIPT_PLAYER_H

#include "../ECS/ECS.h"
#include "../Components/KeyboardControlledComponent.h"
#include "../EventBus/EventBus.h"

class ScriptPlayer: public System {
    Entity* player = nullptr;
    public:
        ScriptPlayer() {
            for(auto entity:GetSystemEntities()){
                if(entity.HasTag("Player")){
                    this->player = &entity;
                }
            }
            RequireComponent<KeyboardControlledComponent>();
        }
        
        void createNewWeapon(){

        }

        void Update(){
            // if(this->player->GetComponent<KeyboardControlledComponent>().rightVelocity > 0.0f ){
            //     auto& animation = assetStore->GetAnimation(textureId);
            //     auto& texture   = assetStore->GetTexture(textureId);
            //     entity.GetComponent<SpriteComponent>()= { 
            //         textureId, texture.width, texture.height , texture.zIndex, texture.isFixed, texture.srcRectX,texture.srcRecY
            //     };
            //     entity.GetComponent<AnimationComponent>() = {
            //         animation.numFrames, animation.frameSpeedRate, animation.horizontal, animation.isLoop
            //     };
            // }
            
        }
};

#endif
