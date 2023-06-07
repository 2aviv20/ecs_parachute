#ifndef MOUSE_MOVE_EVENT_H
#define MOUSE_MOVE_EVENT_H

#include "../ECS/ECS.h"
#include "../EventBus/Event.h"
#include <SDL2/SDL.h>

class MouseMoveEvent: public Event {
    public:
        SDL_Event event;
        MouseMoveEvent(SDL_Event event): event(event) {}
};

#endif
