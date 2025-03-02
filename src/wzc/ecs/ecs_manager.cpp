#include "ecs_manager.h"
#include "system/system.h"
#include "wzc/ecs/component/entity/object_component.h"
#include "wzc/ecs/component/player/player_component.h"

#include <cassert>
#include <stdexcept>

namespace wzc {
    void EcsManager::addSystem(System* system) {
        const std::string& id = system->getId();
        
        std::unordered_set<std::string> allBefore; // every system that should come before this one
        std::unordered_set<std::string> allAfter;  // every system that should come after this one
        
        for (const System* listedSystem : systems) {
            for (const std::string& afterLoopSystem : listedSystem->getAfter()) {
                if (id == afterLoopSystem) allBefore.insert(listedSystem->getId());
                break;
            }
            
            for (const std::string& beforeLoopSystem : listedSystem->getBefore()) {
                if (id == beforeLoopSystem) allAfter.insert(listedSystem->getId());
                break;
            }
        }
        
        // check for duplicates among before and after systems
        for (const std::string& beforeSystem : allBefore) {
            if (allAfter.count(beforeSystem))
                throw std::invalid_argument(
                        "Element " + beforeSystem + " is listed to come before and after this system");
        }
        
        auto it = systems.begin();
        auto lastPrecedingIt = systems.end();
        while (it != systems.end()) {
            if (allBefore.count((*it)->getId()))
                lastPrecedingIt = it;

            ++it;
        }
        
        systems.insert(lastPrecedingIt + 1, system);
    }
    
    void EcsManager::attachObjectComponent(const std::string& objId, ObjectComponent* component) {
        assert(component != nullptr);
        
        objectComponentMap[objId].push_back(component);
    }
    
    void EcsManager::attachPlayerComponent(const std::string& playerId, PlayerComponent* component) {
        assert(component != nullptr);
        
        playerComponentMap[playerId].push_back(component);
    }

    void EcsManager::removeObject(const std::string& objId) {
        const std::vector<ObjectComponent*>& components = objectComponentMap[objId];

        for (const ObjectComponent* component : components) {
            delete component;
        }

        objectComponentMap.erase(objId);
    }

    void EcsManager::removePlayer(const std::string& playerId) {
        const std::vector<PlayerComponent*>& components = playerComponentMap[playerId];

        for (const PlayerComponent* component : components) {
            delete component;
        }

        objectComponentMap.erase(playerId);
    }
    
    bool EcsManager::hasPlayer(const std::string& playerId) const {
        return playerComponentMap.count(playerId);
    }
    
    bool EcsManager::hasObject(const std::string& objId) const {
        return objectComponentMap.count(objId);
    }
    
    void EcsManager::propagate(Event* event) const {
        for (const System* system : systems) {
            assert(system != nullptr);
            
            system->handle(event);
        }
    }
    
    EcsManager::~EcsManager() {
        for (const auto& [objId, componentList] : objectComponentMap) {
            for (const ObjectComponent* component : componentList) {
                delete component;
            }
        }
        
        for (const auto& [objId, componentList] : playerComponentMap) {
            for (const PlayerComponent* component : componentList) {
                delete component;
            }
        }
    }
    
    void EcsManager::removeObjectComponent(const std::string& objId, const std::string& componentId) {
        std::vector<ObjectComponent*>& components = objectComponentMap.at(objId);
        
        for (auto it = components.begin(); it != components.end(); ++it) {
            const auto component = *it;
            
            assert(component != nullptr);
            
            if (component->getTypeId() == componentId) {
                delete component;
                components.erase(it);
                break;
            }
        }
    }
    
    void EcsManager::removePlayerComponent(const std::string& playerId, const std::string& componentId) {
        std::vector<PlayerComponent*>& components = playerComponentMap.at(playerId);
        
        for (auto it = components.begin(); it != components.end(); ++it) {
            const auto component = *it;
            
            assert(component != nullptr);
            
            if (component->getTypeId() == componentId) {
                delete component;
                components.erase(it);
                break;
            }
        }
    }
    
    EcsManager* EcsManager::clone() const {
        auto* clone = new EcsManager();
        
        clone->objectComponentMap = std::unordered_map<std::string, std::vector<ObjectComponent*>>(
                objectComponentMap.size());
        for (const auto& [objId, componentList] : objectComponentMap) {
            clone->objectComponentMap[objId] = std::vector<ObjectComponent*>(componentList.size());
            for (const ObjectComponent* component : componentList) {
                assert(component != nullptr);

                clone->objectComponentMap[objId].push_back(component->clone());
            }
        }
        
        clone->playerComponentMap = std::unordered_map<std::string, std::vector<PlayerComponent*>>(
                playerComponentMap.size());
        for (const auto& [playerId, componentList] : playerComponentMap) {
            clone->playerComponentMap[playerId] = std::vector<PlayerComponent*>(componentList.size());
            for (const PlayerComponent* component : componentList) {
                assert(component != nullptr);

                clone->playerComponentMap[playerId].push_back(component->clone());
            }
        }
        
        return clone;
    }
    
    ObjectComponent* EcsManager::getObjectComponent(const std::string& objId, const std::string& componentId) const {
        const std::vector<ObjectComponent*>& components = getObjectComponents(objId);
        
        for (ObjectComponent* component : components) {
            if (component->getTypeId() == componentId || component->getStrippedId() == componentId) {
                return component;
            }
        }
        
        return nullptr;
    }
    
    PlayerComponent* EcsManager::getPlayerComponent(const std::string& playerId, const std::string& componentId) const {
        const std::vector<PlayerComponent*>& components = getPlayerComponents(playerId);
        
        for (PlayerComponent* component : components) {
            if (component->getTypeId() == componentId || component->getStrippedId() == componentId) {
                return component;
            }
        }
        
        return nullptr;
    }
    
    const std::vector<ObjectComponent*>& EcsManager::getObjectComponents(const std::string& objId) const {
        if (!objectComponentMap.count(objId)) {
            throw std::invalid_argument("Object of ID " + objId + " does not exist");
        }
        
        return objectComponentMap.at(objId);
    }
    
    const std::vector<PlayerComponent*>& EcsManager::getPlayerComponents(const std::string& playerId) const {
        if (!playerComponentMap.count(playerId)) {
            throw std::invalid_argument("Player of ID " + playerId + " does not exist");
        }
        
        return playerComponentMap.at(playerId);
    }
}
