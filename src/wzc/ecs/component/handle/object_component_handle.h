#pragma once

#include <string>

#include "wzc/namespaced_key.h"
#include "wzc/handle/object_handle.h"

namespace wzc {
    struct ObjectComponent;
    struct Game;
    struct GameState;
    
    // A memory-safe way to store object components between game states.
    // Note that this is made for usage inside system handle functions, though it can be used
    // outside them as well. Make sure to use getUnstaged() or existsUnstaged() instead outside of
    // event scope, though.
    struct ObjectComponentHandle final {
        ObjectComponentHandle(const ObjectHandle& owner, const NamespacedKey& key, Game* game);
        ObjectComponentHandle(const ObjectComponentHandle& other) = default;
        
        bool isValid() const; // false if the original game no longer exists
        
        const NamespacedKey& getComponentId() const;
        
        const Game* getGame() const;
        
        bool existsStaged() const;
        bool existsUnstaged() const;
        
        ObjectComponent& getUnstaged() const;
        ObjectComponent& getStaged() const;
        
        ObjectComponent& get() const; // same as getStaged()
        bool exists() const; // same as existsStaged()

        bool existsIn(GameState* gameState) const;
        ObjectComponent& getFrom(GameState* gameState) const;
    
    private:
        ObjectHandle owner;
        NamespacedKey key;
        Game* game;
    };
}
