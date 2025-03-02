#ifndef WARZONECIVILISATION_START_EVENT_H
#define WARZONECIVILISATION_START_EVENT_H

#include "event.h"

namespace wzc {
    struct GameState;
    
    struct StartEvent final : Event {
        explicit StartEvent(GameState* gameState);
        
        const std::string& getTypeId() const override {
            return ID;
        }
        
        static const std::string ID;
    };
}

#endif // WARZONECIVILISATION_START_EVENT_H
