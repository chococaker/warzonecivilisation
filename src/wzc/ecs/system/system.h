#ifndef WARZONECIVILISATION_SYSTEM_H
#define WARZONECIVILISATION_SYSTEM_H

#include <string>
#include <unordered_set>
#include <functional>

namespace wzc {
    struct Event;
    struct EventError;
    
    struct SystemHandler {
        SystemHandler(const SystemHandler& other);
        
        SystemHandler(const std::string& handledEventId,
                      const std::function<void(Event*)>& handleFunction);
        
        const std::string handledEventId; // only handles certain event type
        const std::function<void(Event*)> handleFunction;
        
        bool operator==(const SystemHandler& other) const;
    };
    
    struct SystemHandlerHash {
        size_t operator()(const SystemHandler& handler) const noexcept;
    };
    
    typedef std::unordered_map<std::string, SystemHandler> SystemHandlerMap;
    typedef std::unordered_set<SystemHandler, SystemHandlerHash> SystemHandlerSet;
    
    struct System {
        virtual ~System() = default;

        System(std::string id,
               const SystemHandlerSet& addedHandlers,
               const std::unordered_set<std::string>& before = std::unordered_set<std::string>(),
               const std::unordered_set<std::string>& after = std::unordered_set<std::string>());
        
        void handle(Event* e) const;
        
        virtual const std::string& getId() const = 0;
        
        const std::unordered_set<std::string>& getBefore() const; // systems that should come before
        const std::unordered_set<std::string>& getAfter() const;  // systems that should come after
    private:
        const std::string id;
        
        SystemHandlerMap handlers;
        
        const std::unordered_set<std::string> before;
        const std::unordered_set<std::string> after;
    };
}


#endif //WARZONECIVILISATION_SYSTEM_H
