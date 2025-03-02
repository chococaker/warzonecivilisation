#include "object_component_handle.h"
#include "wzc/game_state.h"
#include "wzc/game.h"
#include <stdexcept>
#include <utility>

#include "wzc/game_object.h"

namespace wzc {
    ObjectComponentHandle::ObjectComponentHandle(const ObjectHandle& owner,
                                                 std::string id,
                                                 Game* game)
            : owner(owner), id(std::move(id)), game(game) { }
    
    const std::string& ObjectComponentHandle::getId() const {
        return id;
    }
    
    const Game* ObjectComponentHandle::getGame() const {
        return game;
    }
    
    bool ObjectComponentHandle::isValid() const {
        return game != nullptr;
    }
    
    bool ObjectComponentHandle::exists() const {
        return existsStaged();
    }
    
    ObjectComponent& ObjectComponentHandle::get() const {
        return getStaged();
    }
    
    bool ObjectComponentHandle::existsStaged() const {
        if (!isValid()) {
            throw std::runtime_error("Handle is no longer valid");
        }
        
        GameState* stagedGameState = game->stagedGameState;
        
        if (stagedGameState == nullptr) {
            throw std::runtime_error("There is no staging in process");
        }
        
        return existsIn(stagedGameState);
    }
    
    bool ObjectComponentHandle::existsUnstaged() const {
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
    
    ObjectComponent& ObjectComponentHandle::getStaged() const {
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
    
    ObjectComponent& ObjectComponentHandle::getUnstaged() const {
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
    
    bool ObjectComponentHandle::existsIn(GameState* gameState) const {
        if (!owner.existsIn(gameState)) {
            return false;
        }
        const std::vector<ObjectComponent*>& components = owner.getFrom(gameState).getComponents();

        for (const ObjectComponent* component : components) {
            if (component->getTypeId() == id) {
                return true;
            }
        }

        return false;
    }
    
    ObjectComponent& ObjectComponentHandle::getFrom(GameState* gameState) const {
        if (!owner.existsIn(gameState)) {
            throw std::invalid_argument("Object " + owner.getId() + " does not exist");
        }
        const std::vector<ObjectComponent*>& components = owner.getFrom(gameState).getComponents();

        for (ObjectComponent* component : components) {
            if (component->getTypeId() == id) {
                return *component;
            }
        }

        throw std::invalid_argument("Object component " + id + " does not exist");
    }
}
