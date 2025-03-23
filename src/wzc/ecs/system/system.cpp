#include "system.h"
#include "event/event.h"
#include <stdexcept>
#include <cassert>
#include <utility>

namespace wzc {
    System::System(const NamespacedKey& key,
                   const SystemHandlerSet& addedHandlers,
                   const std::unordered_set<NamespacedKey, NamespacedKeyHash>& before,
                   const std::unordered_set<NamespacedKey, NamespacedKeyHash>& after)
        : key(key), handlers(addedHandlers.size()), before(before), after(after) {
        for (const auto& handler: addedHandlers) {
            if (handlers.count(handler.handledEventKey)) {
                throw std::invalid_argument("Duplicate handler event ID: " + to_string(handler.handledEventKey));
            }

            handlers.insert({handler.handledEventKey, handler});
        }

        for (const NamespacedKey& system: before) {
            if (after.count(system))
                throw std::invalid_argument("Duplicate system in before & after: " + system.key);
        }
    }

    SystemHandler::SystemHandler(const NamespacedKey& handledEventId,
                                 const std::function<void(Event*, GameState*)>& handleFunction,
                                 bool handleCancelled)
            : handledEventKey(handledEventId), handleFunction(handleFunction), handleCancelled(handleCancelled) { }
    
    bool SystemHandler::operator==(const SystemHandler& other) const {
        return handledEventKey == other.handledEventKey;
    }
    
    void System::handle(Event* e, GameState* gameState) const {
        assert(e != nullptr);
        
        if (handlers.count(e->getTypeKey())) { // if handler exists
            if (const SystemHandler& handler = handlers.at(e->getTypeKey()); !handler.handleCancelled && !e->cancelled) { // handler operates when cancelled
                return handler.handleFunction(e, gameState);
            }
        }
    }
    
    const NamespacedKey& System::getKey() const {
        return key;
    }
    
    const std::unordered_set<NamespacedKey, NamespacedKeyHash>& System::getBefore() const {
        return before;
    }
    
    const std::unordered_set<NamespacedKey, NamespacedKeyHash>& System::getAfter() const {
        return after;
    }
    
    size_t SystemHandlerHash::operator()(const SystemHandler& handler) const noexcept {
        return NamespacedKeyHash{}(handler.handledEventKey);
    }
}
