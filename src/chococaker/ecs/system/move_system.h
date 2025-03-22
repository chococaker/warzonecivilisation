#ifndef WARZONECIVILISATION_HEALING_SYSTEM_H
#define WARZONECIVILISATION_HEALING_SYSTEM_H

#include "wzc/ecs/system/system.h"

namespace ccaker {
    struct MoveSystem final : wzc::System {
        MoveSystem();

        const std::string& getId() const override {
            return ID;
        }
        static const std::string ID;
    private:
        static const wzc::SystemHandler onMove;
    };

}

#endif // WARZONECIVILISATION_HEALING_SYSTEM_H
