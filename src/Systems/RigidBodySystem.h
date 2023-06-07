#ifndef FORCESYSTEM_H
#define FORCESYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/TransformComponent.h"
#include <glm/glm.hpp>

class RigidBodySystem: public System {
    public:
        RigidBodySystem() {
            RequireComponent<RigidBodyComponent>();
            RequireComponent<TransformComponent>();
        }

        void Update(double deltaTime, int ellapsedTime) {
            for (auto entity: GetSystemEntities()) {
                auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
                auto& transform = entity.GetComponent<TransformComponent>();

                glm::vec2 acceleration = rigidBody.sumForces / rigidBody.mass;

                rigidBody.velocity += acceleration * static_cast<float>(deltaTime);
                transform.position += rigidBody.velocity * static_cast<float>(deltaTime);
                 
                rigidBody.clearForces();
            }
        }
};

#endif
