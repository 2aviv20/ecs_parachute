#ifndef TERRAINSYSTEM_H
#define TERRAINSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/HealthComponent.h"
#include "../EventBus/EventBus.h"
#include "../Events/CollisionEvent.h"

class TerrainSystem: public System {
    public:
        TerrainSystem() {
            RequireComponent<BoxColliderComponent>();
        }

        void SubscribeToEvents(const std::shared_ptr<EventBus>& eventBus) {
            eventBus->SubscribeToEvent<CollisionEvent>(this, &TerrainSystem::OnCollision);
        }

        void OnCollision(CollisionEvent& event) {
            Entity a = event.a;
            Entity b = event.b;
            if (a.BelongsToGroup("terrain") && b.BelongsToGroup("weaponGroup")) {
                OnTerrainHit(a, b); // "a" is the projectile, "b" is the player
            }

            if (b.BelongsToGroup("terrain") && a.BelongsToGroup("weaponGroup")){
                OnTerrainHit(b, a); // "b" is the projectile, "a" is the player
            }
        }

        void OnTerrainHit(Entity terrain, Entity meteor) {
            Logger::Log("terrain cillision");
            terrain.Kill();
            meteor.Kill();
        }
};

#endif
