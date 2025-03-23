#pragma once

#include "event.h"

namespace wzc {
    struct GameState;

    // marks the beginning of when events are run through
    struct StartEvent final : Event {
        StartEvent() = default;
        
        const std::string& getTypeId() const override {
            return ID;
        }
        
        static const std::string ID;
    };
}
