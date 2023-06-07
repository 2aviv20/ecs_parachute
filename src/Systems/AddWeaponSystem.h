#ifndef ADD_WEAPON_SYSTEM_H
#define ADD_WEAPON_SYSTEM_H

#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/AddWeaponEvent.h"
class AddWeaponSystem: public System{
    private:
        std::shared_ptr<Registry> registry;
        std::shared_ptr<AssetStore> assetStore;
    public :
        AddWeaponSystem(std::shared_ptr<Registry> registry ,  const std::shared_ptr<AssetStore>& assetStore){
            this->registry = registry;
            this->assetStore = assetStore;
        }

        ~AddWeaponSystem(){

        }

        void SubscribeToEvents(const std::shared_ptr<EventBus>& eventBus){
            eventBus->SubscribeToEvent<AddWeaponEvent>(this, &AddWeaponSystem::OnAddNewWeapon);
        }

        void OnAddNewWeapon(AddWeaponEvent& event){
            Logger::Log("add new Weapon");
            // int mouseX, mouseY;
            // const int buttons = SDL_GetMouseState(&mouseX, &mouseY);
            // Logger::Log("x: " +  std::to_string(mouseX) + " y: " +  std::to_string(mouseY));
            const auto& animation = assetStore->GetAnimation(event.weaponId);
            int spriteWidth = 60;
            int spriteHeight = 60;
            if(animation.num_frames != 0 && animation.speed_rate !=0){
                spriteWidth = animation.width;
                spriteHeight = animation.height;
            }
            Entity newWeapon = registry->CreateEntity(); 
            newWeapon.Group(event.weaponId + "_group");
            newWeapon.Group("weaponGroup");
            newWeapon.AddComponent<TransformComponent>(glm::vec2(1000/2,10), glm::vec2(1.0,1.0),0.0);
            newWeapon.AddComponent<RigidBodyComponent>(glm::vec2(0.0,0.0),1);
            newWeapon.GetComponent<RigidBodyComponent>().addForce(glm::vec2(0,1*9.8));
            newWeapon.AddComponent<SpriteComponent>(event.weaponId,spriteWidth,spriteHeight,6,false,0,0);
            newWeapon.AddComponent<BoxColliderComponent>(50,50,glm::vec2(0.0,5.0));
            if(animation.num_frames != 0 && animation.speed_rate !=0){
                newWeapon.AddComponent<AnimationComponent>(animation.num_frames,animation.speed_rate,animation.horizontal);
            }
        }
};

#endif