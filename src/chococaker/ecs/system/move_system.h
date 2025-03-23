#pragma once

#include "wzc/ecs/system/system.h"

namespace ccaker {
    struct MoveSystem final : wzc::System {
        MoveSystem();

        const wzc::NamespacedKey& getKey() const override {
            return ID;
        }
        static const wzc::NamespacedKey ID;
    private:
        static const wzc::SystemHandler onMove;
    };

}
