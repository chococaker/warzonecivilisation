#pragma once

#include "wzc/namespaced_key.h"
#include "event.h"

namespace wzc {
    struct GameState;

    // marks the end of when events are run through
    struct EndEvent final : Event {
        EndEvent() = default;
        
        const NamespacedKey& getTypeKey() const override {
            return ID;
        }
        
        static const NamespacedKey ID;
    };
}
