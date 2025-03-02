#include "start_event.h"

namespace wzc {
    const std::string StartEvent::ID = "e000@start";
    
    StartEvent::StartEvent(GameState* gameState) : Event(gameState) { }
}
