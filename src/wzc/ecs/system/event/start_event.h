#pragma once

#include "event.h"

#include "wzc/namespaced_key.h"

namespace wzc {
    struct GameState;

    // marks the beginning of when events are run through
    struct StartEvent final : Event {
        StartEvent() = default;
        
        const NamespacedKey& getTypeKey() const override {
            return ID;
        }
        
        static const NamespacedKey ID;
    };
}
