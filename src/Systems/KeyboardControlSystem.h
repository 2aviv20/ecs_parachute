#ifndef KEYBOARDCONTROLSYSTEM_H
#define KEYBOARDCONTROLSYSTEM_H

#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include "../Components/KeyboardControlledComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"

class KeyboardControlSystem: public System {
    public:
        KeyboardControlSystem() {
            RequireComponent<KeyboardControlledComponent>();
            RequireComponent<SpriteComponent>();
            RequireComponent<RigidBodyComponent>();
        }

        void SubscribeToEvents(const std::shared_ptr<EventBus>& eventBus) {
            eventBus->SubscribeToEvent<KeyPressedEvent>(this, &KeyboardControlSystem::OnKeyPressed);
        }

        void OnKeyPressed(KeyPressedEvent& e) {
            for (auto entity: GetSystemEntities()) {
                const auto keyboardcontrol = entity.GetComponent<KeyboardControlledComponent>();
                auto& sprite = entity.GetComponent<SpriteComponent>();
                auto& rigidbody = entity.GetComponent<RigidBodyComponent>();

                switch (e.event.key.keysym.sym) {
                    case SDLK_SPACE:
                        sprite.assetId = (sprite.assetId == "parachute-open") ? "parachute-close" : "parachute-open";
                        break;
                    case SDLK_UP:
                        // rigidbody.velocity = keyboardcontrol.upVelocity;
                        //sprite.srcRect.y = sprite.height * 0;
                        break;
                    case SDLK_RIGHT:
                        rigidbody.velocity = keyboardcontrol.rightVelocity;
                        //sprite.srcRect.y = sprite.height * 1;
                        break;
                    case SDLK_DOWN:
                        // rigidbody.velocity = keyboardcontrol.downVelocity;
                        //sprite.srcRect.y = sprite.height * 2;
                        break;
                    case SDLK_LEFT:
                        rigidbody.velocity = keyboardcontrol.leftVelocity;
                        //sprite.srcRect.y = sprite.height * 3;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        break;
                }
            }
        }

        void Update() {
                
        }
};

#endif

