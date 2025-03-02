#include "object_handle.h"
#include "wzc/game_state.h"
#include "wzc/game.h"
#include "wzc/ecs/ecs_manager.h"
#include <stdexcept>

namespace wzc {
    ObjectHandle::ObjectHandle(const std::string& id,
                               Game* game)
            : id(id), game(game) { }
    
    const std::string& ObjectHandle::getId() const {
        return id;
    }
    
    const Game* ObjectHandle::getGame() const {
        return game;
    }
    
    bool ObjectHandle::isValid() const {
        return game != nullptr;
    }
    
    bool ObjectHandle::exists() const {
        return existsStaged();
    }
    
    GameObject& ObjectHandle::get() const {
        return getStaged();
    }
    
    bool ObjectHandle::existsStaged() const {
        if (!isValid()) {
            throw std::runtime_error("Handle is no longer valid");
        }
        
        GameState* stagedGameState = game->stagedGameState;
        
        if (stagedGameState == nullptr) {
            throw std::runtime_error("There is no staging in process");
        }
        
        return existsIn(stagedGameState);
    }
    
    bool ObjectHandle::existsUnstaged() const {
        if (!isValid()) {
            throw std::runtime_error("Handle is no longer valid");
        }
        
        GameState* unstagedGameState = game->gameState;
        
        if (unstagedGameState == nullptr) {
            // should never happen, but better safe than sorry
            throw std::runtime_error("Game does not have a game state");
        }
        
        return existsIn(unstagedGameState);
    }
    
    GameObject& ObjectHandle::getStaged() const {
        if (!isValid()) {
            throw std::runtime_error("Handle is no longer valid");
        }
        
        GameState* stagedGameState = game->stagedGameState;
        
        if (stagedGameState == nullptr) {
            throw std::runtime_error("There is no staging in process");
        }
        
        if (!existsStaged())
            throw std::runtime_error("Component does not exist");
        
        return getFrom(stagedGameState);
    }
    
    GameObject& ObjectHandle::getUnstaged() const {
        if (!isValid()) {
            throw std::runtime_error("Handle is no longer valid");
        }
        
        GameState* unstagedGameState = game->gameState;
        
        if (unstagedGameState == nullptr) {
            // should never happen, but better safe than sorry
            throw std::runtime_error("Game does not have a game state");
        }
        
        if (!existsUnstaged())
            throw std::runtime_error("Component does not exist");
        
        return getFrom(unstagedGameState);
    }
    
    bool ObjectHandle::existsIn(GameState* gameState) const {
        return gameState->hasObject(id);
    }
    
    GameObject& ObjectHandle::getFrom(GameState* gameState) const {
        return gameState->getObject(id);
    }
}
