#ifndef WARZONECIVILISATION_END_EVENT_H
#define WARZONECIVILISATION_END_EVENT_H

#include "event.h"

namespace wzc {
    struct GameState;

    // marks the end of when events are run through
    struct EndEvent final : Event {
        EndEvent() = default;
        
        const std::string& getTypeId() const override {
            return ID;
        }
        
        static const std::string ID;
    };
}

#endif // WARZONECIVILISATION_END_EVENT_H
