#ifndef MOUSE_EVENT_H
#define MOUSE_EVENT_H

#include "../ECS/ECS.h"
#include "../EventBus/Event.h"
#include <SDL2/SDL.h>

class MouseClickEvent: public Event {
    public:
        SDL_Event event;
        MouseClickEvent(SDL_Event event): event(event) {}
};

#endif
