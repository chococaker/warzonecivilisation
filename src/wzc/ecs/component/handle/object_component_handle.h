#ifndef WARZONECIVILISATION_OBJECT_COMPONENT_HANDLE_H
#define WARZONECIVILISATION_OBJECT_COMPONENT_HANDLE_H

#include <string>

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
        ObjectComponentHandle(const ObjectHandle& owner, std::string  id, Game* game);
        ObjectComponentHandle(const ObjectComponentHandle& other) = default;
        
        bool isValid() const; // false if the original game no longer exists
        
        const std::string& getId() const;
        
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
        std::string id;
        Game* game;
    };
}

#endif // WARZONECIVILISATION_OBJECT_COMPONENT_HANDLE_H
