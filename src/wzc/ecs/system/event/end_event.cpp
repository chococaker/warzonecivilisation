#include "end_event.h"

namespace wzc {
    const std::string EndEvent::ID = "e000@end";
    
    EndEvent::EndEvent(GameState* gameState) : Event(gameState) { }
}
