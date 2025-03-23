#pragma once

#include <string>

#include "wzc/handle/player_handle.h"

namespace wzc {
    struct PlayerComponent;
    struct Game;
    struct GameState;
    
    // A memory-safe way to store player components between game states.
    // Note that this is made for usage inside system handle functions, though it can be used
    // outside them as well. Make sure to use getUnstaged() or existsUnstaged() instead outside of
    // event scope, though.
    struct PlayerComponentHandle final {
        PlayerComponentHandle(const PlayerHandle& owner, std::string id, Game* game);
        PlayerComponentHandle(const PlayerComponentHandle& other) = default;
        
        bool isValid() const; // false if the original game no longer exists
        
        const std::string& getId() const;
        
        const Game* getGame() const;
        
        bool existsStaged() const;
        bool existsUnstaged() const;
        
        PlayerComponent& getUnstaged() const;
        PlayerComponent& getStaged() const;
        
        PlayerComponent& get() const; // same as getStaged()
        bool exists() const; // same as existsStaged()

        bool existsIn(GameState* gameState) const;
        PlayerComponent& getFrom(GameState* gameState) const;

    private:
        const PlayerHandle owner;
        const std::string id;
        Game* game;
    };
}
