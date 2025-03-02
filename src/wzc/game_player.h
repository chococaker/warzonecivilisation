#ifndef WARZONECIVILISATION_GAME_PLAYER_H
#define WARZONECIVILISATION_GAME_PLAYER_H

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

        PlayerComponent& getComponent(const std::string& componentTypeId) const;

        template<typename T>
        T& getComponent(const std::string& componentTypeId);

        // attaches a component to the player. overrides previous component if it exists
        void attachComponent(const PlayerComponent& component);

        void removeComponent(const std::string& componentTypeId);

        bool hasComponent(const std::string& componentTypeId) const;
    
    private:
        std::string id;
        size_t turn;
        std::vector<PlayerComponent*> components;
    };

    template<typename T>
    T& GamePlayer::getComponent(const std::string& componentTypeId) {
        PlayerComponent& component = getComponent(componentTypeId);

        try {
            T& t = dynamic_cast<T&>(component);
            return t;
        } catch (const std::bad_cast&) {
            throw std::invalid_argument("Object component " + componentTypeId + " is not of the requested template type");
        }
    }
}


#endif //WARZONECIVILISATION_GAME_PLAYER_H
