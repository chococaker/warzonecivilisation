#include "system.h"
#include "event/event.h"
#include <stdexcept>
#include <cassert>
#include <utility>

namespace wzc {
    System::System(std::string  id,
                   const SystemHandlerSet& addedHandlers,
                   const std::unordered_set<std::string>& before,
                   const std::unordered_set<std::string>& after)
            : id(std::move(id)), before(before), after(after) {
        for (const auto& handler : addedHandlers) {
            if (handlers.count(handler.handledEventId)) {
                throw std::invalid_argument("Duplicate handler event ID: " + handler.handledEventId);
            }
            
            handlers.insert({handler.handledEventId, handler});
        }
        
        for (const std::string& system : before) {
            if (after.count(system))
                throw std::invalid_argument("Duplicate system in before & after: " + system);
        }
    }

    SystemHandler::SystemHandler(const std::string& handledEventId,
                                 const std::function<void(Event*)>& handleFunction,
                                 bool handleCancelled)
            : handledEventId(handledEventId), handleFunction(handleFunction), handleCancelled(handleCancelled) { }
    
    bool SystemHandler::operator==(const SystemHandler& other) const {
        return handledEventId == other.handledEventId;
    }
    
    void System::handle(Event* e) const {
        assert(e != nullptr);
        
        if (handlers.count(e->getTypeId())) { // if handler exists
            if (const SystemHandler& handler = handlers.at(e->getTypeId()); !handler.handleCancelled && !e->cancelled) { // handler operates when cancelled
                return handler.handleFunction(e);
            }
        }
    }
    
    const std::string& System::getId() const {
        return id;
    }
    
    const std::unordered_set<std::string>& System::getBefore() const {
        return before;
    }
    
    const std::unordered_set<std::string>& System::getAfter() const {
        return after;
    }
    
    size_t SystemHandlerHash::operator()(const SystemHandler& handler) const noexcept {
        return std::hash<std::string>{}(handler.handledEventId);
    }
}
