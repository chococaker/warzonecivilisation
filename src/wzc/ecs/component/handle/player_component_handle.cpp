#include "player_component_handle.h"
#include "wzc/game_state.h"
#include "wzc/game.h"
#include <stdexcept>
#include <utility>

#include "wzc/game_player.h"

namespace wzc {
    PlayerComponentHandle::PlayerComponentHandle(const PlayerHandle& owner,
                                                 const NamespacedKey& key,
                                                 Game* game)
            : owner(owner), componentKey(key), game(game) { }
    
    const NamespacedKey& PlayerComponentHandle::getComponentId() const {
        return componentKey;
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
        if (!owner.existsIn(gameState)) {
            return false;
        }
        const std::vector<PlayerComponent*>& components = owner.getFrom(gameState).getComponents();

        for (const PlayerComponent* component : components) {
            if (component->getTypeKey() == componentKey) {
                return true;
            }
        }

        return false;
    }

    PlayerComponent& PlayerComponentHandle::getFrom(GameState* gameState) const {
        if (!owner.existsIn(gameState)) {
            throw std::invalid_argument("Player " + owner.getId() + " does not exist");
        }
        const std::vector<PlayerComponent*>& components = owner.getFrom(gameState).getComponents();

        for (PlayerComponent* component : components) {
            if (component->getTypeKey() == componentKey) {
                return *component;
            }
        }

        throw std::invalid_argument("Player component " + to_string(componentKey) + " does not exist");
    }
}
