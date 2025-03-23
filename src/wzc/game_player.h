#pragma once

#include "ecs/component/player/player_component.h"

#include <string>
#include <vector>
#include <stdexcept>

namespace wzc {
    /**
     * Deleted by Game.
     */
    struct GamePlayer {
        GamePlayer(const std::string& id, size_t turn);
        GamePlayer(const GamePlayer& other);
        
        const std::string& getId() const;
        size_t getTurn() const;
        
        bool operator==(const GamePlayer& other) const;

        const std::vector<PlayerComponent*>& getComponents() const;

        PlayerComponent& getComponent(const NamespacedKey& componentTypeId) const;

        template<typename T>
        T& getComponent(const NamespacedKey& componentTypeId);

        // attaches a component to the player. overrides previous component if it exists
        void attachComponent(const PlayerComponent& component);

        void removeComponent(const NamespacedKey& componentTypeId);

        bool hasComponent(const NamespacedKey& componentTypeId) const;
    
    private:
        std::string id;
        size_t turn;
        std::vector<PlayerComponent*> components;
    };

    template<typename T>
    T& GamePlayer::getComponent(const NamespacedKey& componentTypeId) {
        PlayerComponent& component = getComponent(componentTypeId);

        try {
            T& t = dynamic_cast<T&>(component);
            return t;
        } catch (const std::bad_cast&) {
            throw std::invalid_argument("Object component " + to_string(componentTypeId) + " is not of the requested template type");
        }
    }
}
