#ifndef WARZONECIVILISATION_OBJECT_HANDLE_H
#define WARZONECIVILISATION_OBJECT_HANDLE_H

#include <string>

namespace wzc {
    struct GameObject;
    struct Game;
    struct GameState;
    
    // A memory-safe way to store objects between game states.
    // Note that this is made for usage inside system handle functions, though it can be used
    // outside them as well. Make sure to use getUnstaged() or existsUnstaged() instead outside of
    // event scope, though.
    struct ObjectHandle final {
        ObjectHandle(const std::string& id, Game* game);
        ObjectHandle(const ObjectHandle& other) = default;
        
        bool isValid() const; // false if the original game no longer exists
        
        const std::string& getId() const;
        
        const Game* getGame() const;
        
        bool existsStaged() const;
        bool existsUnstaged() const;
        
        GameObject& getUnstaged() const;
        GameObject& getStaged() const;
        
        GameObject& get() const; // same as getStaged()
        bool exists() const; // same as existsStaged()

        GameObject& getFrom(GameState* gameState) const;
        bool existsIn(GameState* gameState) const;

    private:
        std::string id;
        Game* game;
    };
}

#endif // WARZONECIVILISATION_OBJECT_HANDLE_H
