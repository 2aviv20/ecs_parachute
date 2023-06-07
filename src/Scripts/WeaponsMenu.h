#ifndef SCRIPT_WEAPONS_MENU_H
#define SCRIPT_WEAPONS_MENU_H

#include <SDL2/SDL.h>
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include "../Components/KeyboardControlledComponent.h"
#include "../Components/TransformComponent.h"
#include "../Events/AddWeaponEvent.h"
#include "../EventBus/EventBus.h"
#include "../Events/MouseClickEvent.h"
#include "../Events/MouseMoveEvent.h"

struct WeaponIcon{
    std::string iconName;
    SDL_Rect    iconRect;
};

class WeaponsMenu: public System {
    private:
        bool showMenu = false;
        std::shared_ptr<EventBus> eventBus;
        Entity entity;
        SDL_Color menuBarColor = {255, 255, 255};
        SDL_Color selectedWeaponColor = {255, 0, 255};
        int mapWidth ;
        int mapHeight;
        int menuWidth = 80;
        int menuHeight = 150;
        int padding = 15;

        double menuBarPosX;
        double menuBarPosY;
        const SDL_Rect& camera;

        std::map<std::string , WeaponIcon> weapons;
        

        std::string selectedWeapon = "";

    public:
        // TODO : remove "member initializer list"
        WeaponsMenu(std::shared_ptr<EventBus> eventBus, std::shared_ptr<Registry> registry, int mapWidth , int mapHeight, SDL_Rect& camera) : eventBus(eventBus) , entity(registry->CreateEntity()) ,mapWidth(mapWidth) ,mapHeight(mapHeight), camera(camera) {
            RequireComponent<KeyboardControlledComponent>();

            weapons["weapon-missile"] = WeaponIcon {"weapon-icon-bazooka-1",{0,0,0,0}};
            weapons["weapon-hmissil-1"] = WeaponIcon {"weapon-icon-hmissile-1",{0,0,0,0}};
            weapons["weapon-spsheep"] = WeaponIcon {"weapon-icon-sprsheep-1" ,{0,0,0,0}};
            weapons["weapon-meteor"] = WeaponIcon {"weapon-icon-meteor-1" ,{0,0,0,0}};
            // entity = registry->CreateEntity();
            entity.Tag("WeaponsMenu");
            entity.AddComponent<TransformComponent>(
                glm::vec2(
                    0,
                    0
                ),//position
                glm::vec2(
                    1.0,
                    1.0
                ),//scale
                0.0//rotation
            );
            const auto& transform = entity.GetComponent<TransformComponent>();
            this->menuBarPosX = (mapWidth - (menuWidth * transform.scale.x) - padding) - camera.x;
            this->menuBarPosY = (mapHeight - (menuHeight * transform.scale.y) - padding) - camera.y;
            initMenuIconsRect();
        }

        void SubscribeToEvents(std::shared_ptr<EventBus>& eventBus){
            eventBus->SubscribeToEvent<MouseClickEvent>(this, &WeaponsMenu::OnMouseButtonPressed);
            eventBus->SubscribeToEvent<MouseMoveEvent>(this,  &WeaponsMenu::OnMouseMove);
        }

        void render(SDL_Renderer* renderer, const std::shared_ptr<AssetStore>& assetStore){
            // exit render function if menu should be hidden exit render funtion 
            if(!showMenu){
                return;
            }
            //render menu box shape
            const auto& transform = entity.GetComponent<TransformComponent>();
            int padding = 15;
            menuBarPosX = (mapWidth - (menuWidth * transform.scale.x) - padding) - camera.x;
            menuBarPosY = (mapHeight - (menuHeight * transform.scale.y) - padding) - camera.y;

            SDL_Rect menuBarRectangle = {
                static_cast<int>(menuBarPosX),
                static_cast<int>(menuBarPosY),
                static_cast<int>(menuWidth),
                static_cast<int>(menuHeight)
            };
            SDL_SetRenderDrawColor(renderer, menuBarColor.r, menuBarColor.g, menuBarColor.b, 255);
            SDL_RenderFillRect(renderer, &menuBarRectangle);
            
            // render weapons icons
            std::map<std::string, WeaponIcon>::iterator weaponsIterator;
            for (weaponsIterator = weapons.begin(); weaponsIterator != weapons.end(); weaponsIterator++)
            {
                std::string iconId = weaponsIterator->second.iconName;
                SDL_RenderCopyEx(
                    renderer,
                    assetStore->GetTexture(iconId),
                    NULL,
                    &weaponsIterator->second.iconRect,
                    transform.rotation,
                    NULL,
                    SDL_FLIP_NONE
                );
                if(selectedWeapon == weaponsIterator->first){
                    SDL_SetRenderDrawColor(renderer, selectedWeaponColor.r, selectedWeaponColor.g, selectedWeaponColor.b, 255);
                    SDL_RenderDrawRect(renderer, &weaponsIterator->second.iconRect);
                }else{
                    SDL_SetRenderDrawColor(renderer, menuBarColor.r, menuBarColor.g, menuBarColor.b, 255);
                    SDL_RenderDrawRect(renderer, &weaponsIterator->second.iconRect);
                }
                
            }
        }

        void initMenuIconsRect(){
            const auto& transform = entity.GetComponent<TransformComponent>();
            int spriteWidth = 32;
            int spriteHeight = 32;
            int iconPosX = menuBarPosX;
            int iconPosY = menuBarPosY;
            int i = 0;
            std::map<std::string, WeaponIcon>::iterator weaponsIterator;

            for (weaponsIterator = weapons.begin(); weaponsIterator != weapons.end(); weaponsIterator++)
            {
                weaponsIterator->second.iconRect = {
                    static_cast<int>(iconPosX),
                    static_cast<int>(iconPosY),
                    static_cast<int>(spriteWidth * transform.scale.x),
                    static_cast<int>(spriteHeight * transform.scale.y)
                };
                
                i++;
                iconPosX +=32;

                if(i%2 == 0){
                    iconPosY += spriteHeight;
                    iconPosX -= 64;
                }
                Logger::Log(std::to_string(weaponsIterator->second.iconRect.x));
            }
        }

        void Update(std::unique_ptr<EventBus>& eventBus){
            //listen to mouse right click open/close menu 
        }

    

        void OnMouseButtonPressed(MouseClickEvent& e){
            if (e.event.button.button == SDL_BUTTON_RIGHT) {
                showMenu = !showMenu;
                Logger::Log("showMenu : " + std::to_string(showMenu));
            }
            if(e.event.button.button == SDL_BUTTON_LEFT && selectedWeapon != ""){
                eventBus->EmitEvent<AddWeaponEvent>(selectedWeapon, (mapWidth/2),0);
            }
        }

        void OnMouseMove(MouseMoveEvent& e){
            int mouseX = e.event.motion.x;
            int mouseY = e.event.motion.y;
            if(showMenu && 
               (mouseX >=menuBarPosX && mouseX <= menuBarPosX + menuWidth) &&
               (mouseY >=menuBarPosY && mouseY <= menuBarPosY + menuHeight)){
                // TODO : check for collsion
                std::map<std::string, WeaponIcon>::iterator weaponsIterator;
                for (weaponsIterator = weapons.begin(); weaponsIterator != weapons.end(); weaponsIterator++)
                {
                    int iconX = weaponsIterator->second.iconRect.x;
                    int iconY = weaponsIterator->second.iconRect.y;
                    int iconW = weaponsIterator->second.iconRect.w;
                    int iconH = weaponsIterator->second.iconRect.h;
                    if(showMenu && 
                    (mouseX >=iconX && mouseX <= iconX + iconW) &&
                    (mouseY >=iconY && mouseY <= iconY + iconH)){
                        selectedWeapon = weaponsIterator->first;
                    }
                }
                //TODO : if collsion true change the border color 
            }else{
                selectedWeapon = "";
            }
        }
};

#endif
