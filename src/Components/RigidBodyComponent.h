#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

#include <glm/glm.hpp>

struct RigidBodyComponent {
    glm::vec2 velocity;
    glm::vec2 sumForces;
    float mass;
    RigidBodyComponent(glm::vec2 velocity = glm::vec2(0.0, 0.0),float mass = 0) {
        this->velocity = velocity;
        this->mass = mass;
        this->sumForces = glm::vec2(0,0);
    }
     void addWeightForce(){
        this->sumForces = glm::vec2(0,1*9.8f);
    }

    void addForce(glm::vec2 force){
        this->sumForces += force;
    }

    void clearForces(){
        this->sumForces = glm::vec2(0,0);
    }
};

#endif
