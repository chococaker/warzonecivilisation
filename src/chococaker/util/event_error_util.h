#ifndef WARZONECIVILISATION_ERROR_UTIL
#define WARZONECIVILISATION_ERROR_UTIL

#include <string>
#include <stdexcept>
#include "wzc/game_state.h"
#include "wzc/game_object.h"
#include "wzc/game_player.h"
#include "wzc/ecs/component/entity/object_component.h"
#include "wzc/ecs/component/player/player_component.h"
#include "wzc/error/id_type_mismatch.h"

#include "chococaker/ecs/system/event/generic_errors.h"


namespace ccaker {
    // Retrieves an object component of a certain type from a GameState.
    // If the component is not found, a ComponentNeededError is thrown, which is an EventError.
    template<typename T>
    T& getObjectComponent(wzc::GameState* gameState, const std::string& ownerId) {
        if (!gameState->hasObjectComponent(ownerId, T::ID)) {
            throw ComponentNeededError(T::ID, false, T::ID);
        }
        
        try {
            T& component = gameState->getObjectComponent<T>(ownerId);
            return component;
        } catch (const std::invalid_argument&) {
            throw wzc::IdTypeMismatch(T::ID, typeid(T));
        }
    }
    
    // Retrieves a player component of a certain type from a GameState.
    // If the component is not found, a ComponentNeededError is thrown, which is an EventError.
    template<typename T>
    T& getPlayerComponent(wzc::GameState* gameState, const std::string& ownerId) {
        if (!gameState->hasObjectComponent(ownerId, T::ID)) {
            throw ComponentNeededError(T::ID, false, T::ID);
        }
        
        try {
            T& component = gameState->getPlayerComponent<T>(ownerId);
            return component;
        } catch (const std::invalid_argument&) {
            throw wzc::IdTypeMismatch(T::ID, typeid(T));
        }
    }
    
    // Retrieves an object component of a certain type from a GameState.
    // If the component is not found, a ComponentNeededError is thrown, which is an EventError.
    template<typename T>
    T& getComponent(wzc::GameState* gameState, const wzc::GameObject& owner) {
        return getObjectComponent<T>(gameState, owner.getId());
    }
    
    // Retrieves a player component of a certain type from a GameState.
    // If the component is not found, a ComponentNeededError is thrown, which is an EventError.
    template<typename T>
    T& getComponent(wzc::GameState* gameState, const wzc::GamePlayer& owner) {
        return getPlayerComponent<T>(gameState, owner.getId());
    }
}

#endif // WARZONECIVILISATION_ERROR_UTIL