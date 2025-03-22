#ifndef WARZONECIVILISATION_ERROR_UTIL
#define WARZONECIVILISATION_ERROR_UTIL

#include <string>
#include <stdexcept>
#include "wzc/game_object.h"
#include "wzc/game_player.h"
#include "wzc/error/id_type_mismatch.h"


namespace ccaker {
    // Retrieves an object component of a certain type from a GameState.
    // If the component is not found, a ComponentNeededError is thrown, which is an EventError.
    template<typename T>
    T& getComponent(wzc::GameObject& owner) {
        try {
            T& component = owner.getComponent<T>(T::ID);
            return component;
        } catch (const std::invalid_argument&) {
            throw wzc::IdTypeMismatch(T::ID, typeid(T));
        }
    }
    
    // Retrieves a player component of a certain type from a GameState.
    // If the component is not found, a ComponentNeededError is thrown, which is an EventError.
    template<typename T>
    T& getComponent(wzc::GamePlayer& owner) {
        try {
            T& component = owner.getComponent<T>(T::ID);
            return component;
        } catch (const std::invalid_argument&) {
            throw wzc::IdTypeMismatch(T::ID, typeid(T));
        }
    }
}

#endif // WARZONECIVILISATION_ERROR_UTIL