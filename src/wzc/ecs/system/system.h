#pragma once

#include "wzc/namespaced_key.h"

#include <string>
#include <unordered_set>
#include <functional>

namespace wzc {
    struct Event;
    struct EventError;
    struct GameState;
    
    struct SystemHandler {
        SystemHandler(const SystemHandler& other) = default;
        
        SystemHandler(const NamespacedKey& handledEventId,
                      const std::function<void(Event*, GameState*)>& handleFunction,
                      bool handleCancelled);
        
        const NamespacedKey handledEventKey; // only handles certain event type
        const std::function<void(Event*, GameState*)> handleFunction;
        const bool handleCancelled;
        
        bool operator==(const SystemHandler& other) const;
    };
    
    struct SystemHandlerHash {
        size_t operator()(const SystemHandler& handler) const noexcept;
    };
    
    typedef std::unordered_map<const NamespacedKey, SystemHandler, NamespacedKeyHash> SystemHandlerMap;
    typedef std::unordered_set<SystemHandler, SystemHandlerHash> SystemHandlerSet;
    
    struct System {
        virtual ~System() = default;

        System(const NamespacedKey& key,
               const SystemHandlerSet& addedHandlers,
               const std::unordered_set<NamespacedKey, NamespacedKeyHash>& before = std::unordered_set<NamespacedKey, NamespacedKeyHash>(),
               const std::unordered_set<NamespacedKey, NamespacedKeyHash>& after = std::unordered_set<NamespacedKey, NamespacedKeyHash>());
        
        void handle(Event* e, GameState* gameState) const;
        
        virtual const NamespacedKey& getKey() const = 0;
        
        const std::unordered_set<NamespacedKey, NamespacedKeyHash>& getBefore() const; // systems that should come before
        const std::unordered_set<NamespacedKey, NamespacedKeyHash>& getAfter() const;  // systems that should come after
    private:
        const NamespacedKey key;
        
        SystemHandlerMap handlers;
        
        const std::unordered_set<NamespacedKey, NamespacedKeyHash> before;
        const std::unordered_set<NamespacedKey, NamespacedKeyHash> after;
    };
}
