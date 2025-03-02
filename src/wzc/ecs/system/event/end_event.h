#ifndef WARZONECIVILISATION_END_EVENT_H
#define WARZONECIVILISATION_END_EVENT_H

#include "event.h"

namespace wzc {
    struct GameState;
    
    struct EndEvent final : Event {
        explicit EndEvent(GameState* gameState);
        
        const std::string& getTypeId() const override {
            return ID;
        }
        
        static const std::string ID;
    };
}

#endif // WARZONECIVILISATION_END_EVENT_H
