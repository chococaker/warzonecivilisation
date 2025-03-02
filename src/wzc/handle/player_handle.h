#ifndef WARZONECIVILISATION_PLAYER_HANDLE_H
#define WARZONECIVILISATION_PLAYER_HANDLE_H

#include <string>

namespace wzc {
    struct GamePlayer;
    struct Game;
    struct GameState;
    
    // A memory-safe way to store players between game states.
    // Note that this is made for usage inside system handle functions, though it can be used
    // outside them as well. Make sure to use getUnstaged() or existsUnstaged() instead outside of
    // event scope, though.
    struct PlayerHandle final {
        PlayerHandle(const std::string& id, Game* game);
        PlayerHandle(const PlayerHandle& other) = default;
        
        bool isValid() const; // false if the original game no longer exists
        
        const std::string& getId() const;
        
        const Game* getGame() const;
        
        bool existsStaged() const;
        bool existsUnstaged() const;
        
        GamePlayer& getUnstaged() const;
        GamePlayer& getStaged() const;
        
        GamePlayer& get() const; // same as getStaged()
        bool exists() const; // same as existsStaged()
        
    private:
        std::string id;
        Game* game;
        
        bool existsIn(const GameState* gameState) const;
        GamePlayer& getFrom(GameState* gameState) const;
    };
}

#endif // WARZONECIVILISATION_PLAYER_HANDLE_H
