#ifndef ADD_WEAPON_EVENT_H
#define ADD_WEAPON_EVENT_H

#include "../ECS/ECS.h"
#include "../EventBus/Event.h"

class AddWeaponEvent: public Event {
    public:
        std::string weaponId;
        int x;
        int y;
        AddWeaponEvent(std::string weaponId ,int x, int y):  weaponId(weaponId), x(x), y(y) {}
};

#endif
