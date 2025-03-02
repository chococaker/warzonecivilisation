#include "game_player.h"

#include "ecs/component/player/player_component.h"
#include "error/component_not_found.h"

#include <algorithm>
#include <cassert>
#include <vector>

namespace wzc {
    GamePlayer::GamePlayer(const std::string& id, const size_t turn)
            : id(id), turn(turn) {}

    GamePlayer::GamePlayer(const GamePlayer& other)
        : id(other.id), turn(other.turn) {
        components.reserve(other.components.size());
        for (const auto& component : other.components) {
            components.push_back(component->clone());
        }
    }
    
    const std::string& GamePlayer::getId() const {
        return id;
    }
    
    size_t GamePlayer::getTurn() const {
        return turn;
    }
    
    bool GamePlayer::operator==(const GamePlayer& other) const {
        return turn == other.turn;
    }


    const std::vector<PlayerComponent*>& GamePlayer::getComponents() const {
        return components;
    }

    PlayerComponent& GamePlayer::getComponent(const std::string& componentTypeId) const {
        for (PlayerComponent* component : components) {
            if (component->getTypeId() == componentTypeId) {
                return *component;
            }
        }

        throw ComponentNotFound(componentTypeId);
    }

    void GamePlayer::attachComponent(const PlayerComponent& component) {
        // check if component is already in components
        size_t index = 0;
        for (const PlayerComponent* ownedComponent : components) {
            if (ownedComponent->getTypeId() == component.getTypeId()) {}
            index++;
        }

        PlayerComponent* newComponent = component.clone();

        if (index != components.size()) {
            components[index] = newComponent;
        } else {
            components.push_back(newComponent);
        }
    }

    void GamePlayer::removeComponent(const std::string& componentTypeId) {
        components.erase(std::remove_if(components.begin(), components.end(),
            [componentTypeId](const PlayerComponent* component) {
                return component->getTypeId() == componentTypeId;
            }), components.end());
    }

    bool GamePlayer::hasComponent(const std::string& componentTypeId) const {
        for (const PlayerComponent* component : components) {
            if (component->getTypeId() == componentTypeId) {
                return true;
            }
        }

        return false;
    }
}
