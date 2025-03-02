#include "player_component_handle.h"
#include "wzc/game_state.h"
#include "wzc/game.h"
#include "wzc/ecs/ecs_manager.h"
#include <stdexcept>
#include <utility>

namespace wzc {
    PlayerComponentHandle::PlayerComponentHandle(std::string owner,
                                                 std::string id,
                                                 Game* game)
            : owner(std::move(owner)), id(std::move(id)), game(game) { }
    
    const std::string& PlayerComponentHandle::getId() const {
        return id;
    }
    
    const Game* PlayerComponentHandle::getGame() const {
        return game;
    }
    
    bool PlayerComponentHandle::isValid() const {
        return game != nullptr;
    }
    
    bool PlayerComponentHandle::exists() const {
        return existsStaged();
    }
    
    PlayerComponent& PlayerComponentHandle::get() const {
        return getStaged();
    }
    
    bool PlayerComponentHandle::existsStaged() const {
        if (!isValid()) {
            throw std::runtime_error("Handle is no longer valid");
        }
        
        GameState* stagedGameState = game->stagedGameState;
        
        if (stagedGameState == nullptr) {
            throw std::runtime_error("There is no staging in process");
        }
        
        return existsIn(stagedGameState);
    }
    
    bool PlayerComponentHandle::existsUnstaged() const {
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
    
    PlayerComponent& PlayerComponentHandle::getStaged() const {
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
    
    PlayerComponent& PlayerComponentHandle::getUnstaged() const {
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
    
    bool PlayerComponentHandle::existsIn(GameState* gameState) const {
        return gameState->hasPlayer(owner)
               && gameState->hasPlayerComponent(owner, id);
    }
    
    PlayerComponent& PlayerComponentHandle::getFrom(GameState* gameState) const {
        return gameState->getPlayerComponent(owner, id);
    }
}
