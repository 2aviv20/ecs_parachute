#ifndef KEYPRESSEDEVENT_H
#define KEYPRESSEDEVENT_H

#include "../ECS/ECS.h"
#include "../EventBus/Event.h"
#include <SDL2/SDL.h>

class KeyPressedEvent: public Event {
    public:
        SDL_Event event;
        KeyPressedEvent(SDL_Event event): event(event) {}
};

#endif
