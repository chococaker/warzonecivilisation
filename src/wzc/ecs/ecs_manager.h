#ifndef WARZONECIVILISATION_ECS_MANAGER_H
#define WARZONECIVILISATION_ECS_MANAGER_H

#include <string>
#include <vector>
#include <unordered_map>

namespace wzc {
    struct System;
    struct ObjectComponent;
    struct PlayerComponent;
    struct GameState;
    struct Event;
    
    // EcsManager takes ownership of all added components
    struct EcsManager {
        void addSystem(System* system); // does not take ownership of system
        // takes ownership of component. if the occupant does not exist, it will be created.
        void attachObjectComponent(const std::string& objId, ObjectComponent* component);
        // takes ownership of component. if the player does not exist, it will be created.
        void attachPlayerComponent(const std::string& playerId, PlayerComponent* component);

        void removeObject(const std::string& objId);
        void removePlayer(const std::string& playerId);
        
        bool hasPlayer(const std::string& playerId) const;
        bool hasObject(const std::string& objId) const;
        
        // deletes component from memory
        void removeObjectComponent(const std::string& objId, const std::string& componentId);
        void removePlayerComponent(const std::string& playerId, const std::string& componentId);
        
        ObjectComponent* getObjectComponent(const std::string& objId, const std::string& componentId) const;
        PlayerComponent* getPlayerComponent(const std::string& playerId, const std::string& componentId) const;
        
        const std::vector<ObjectComponent*>& getObjectComponents(const std::string& objId) const;
        const std::vector<PlayerComponent*>& getPlayerComponents(const std::string& playerId) const;
        
        void propagate(Event* event) const;
        
        EcsManager* clone() const;
        
        ~EcsManager(); // deletes components
    private:
        friend GameState;
        
        std::vector<System*> systems;
        
        std::unordered_map<std::string, std::vector<ObjectComponent*>> objectComponentMap;
        std::unordered_map<std::string, std::vector<PlayerComponent*>> playerComponentMap;
    };
}


#endif //WARZONECIVILISATION_ECS_MANAGER_H
