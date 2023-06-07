#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <SDL2/SDL.h>

struct AnimationComponent {
    int numFrames;
    int currentFrame;
    int frameSpeedRate;
    bool isLoop;
    int startTime;
    bool horizontal;

    AnimationComponent(int numFrames = 1, int frameSpeedRate = 1, bool horizontal = true , bool isLoop = true) {
        this->numFrames = numFrames;
        this->currentFrame = 1;
        this->frameSpeedRate = frameSpeedRate;
        this->isLoop = isLoop;
        this->horizontal = horizontal;
        this->startTime = SDL_GetTicks();
    }
};

#endif
