#include "game_state.h"
#include "game.h"
#include "wzc/game_player.h"
#include "wzc/game_object.h"
#include "wzc/ecs/ecs_manager.h"
#include "wzc/game_type_map.h"

#include "wzc/ecs/component/entity/object_component.h"
#include "wzc/ecs/component/player/player_component.h"
#include "wzc/ecs/prefab/object_prefab.h"
#include "wzc/ecs/prefab/player_prefab.h"

#include <algorithm>
#include <cassert>
#include <stdexcept>

namespace wzc {
    GameState::GameState(const TileTypeMap* tileTypeMap,
                         tagMTRand* rand,
                         const int16_t latestObjectId,
                         Game* game)
            : ecsManager(new EcsManager()),
              typeMap(tileTypeMap),
              currentTurn(0),
              latestObjectId(latestObjectId),
              rand(rand),
              game(game) { }
    
    GameState::GameState(const GameState& other)
            : typeMap(other.typeMap),
              currentTurn(other.currentTurn),
              latestObjectId(other.latestObjectId),
              rand(other.rand),
              game(other.game) {
        if (other.ecsManager == nullptr) {
            throw std::invalid_argument("Other GameState (" + other.getQualifiedId() + ") contains null ECS Manager");
        }
        ecsManager = other.ecsManager->clone();
    }
    
    size_t GameState::getCurrentTurn() const {
        return currentTurn;
    }
    
    GamePlayer& GameState::getCurrentPlayer() {
        return getPlayerAt(currentTurn);
    }
    
    GamePlayer& GameState::getPlayerAt(const size_t turn) {
        if (turn > players.size() - 1)
            throw std::invalid_argument("Turn number exceeds max turns");
        
        GamePlayer& player = players.at(turn);
        
        return player;
    }
    
    GameObject& GameState::getObject(const std::string& objId) {
        for (GameObject& object : objects) {
            if (object.getId() == objId) return object;
        }
        
        throw std::invalid_argument("Object " + objId + " does not exist");
    }
    
    GameObject& GameState::getObject(const math::Vector2& location) {
        for (GameObject& object : objects) {
            if (object.getLocation() == location) return object;
        }
        
        throw std::invalid_argument("Object at " + to_string(location) + " does not exist");
    }
    
    GamePlayer& GameState::getPlayer(const std::string& playerId) {
        for (GamePlayer& player : players) {
            if (player.getId() == playerId) return player;
        }
        
        throw std::invalid_argument("Player " + playerId + " does not exist");
    }
    
    bool GameState::hasPlayer(const std::string& playerId) const {
        return std::any_of(players.begin(), players.end(),
                           [&] (const GamePlayer& player) -> bool { return player.getId() == playerId; });
    }
    
    bool GameState::hasObject(const std::string& objId) const {
        return std::any_of(objects.begin(), objects.end(),
                           [&] (const GameObject& object) -> bool { return object.getId() == objId; });
    }
    
    std::vector<std::string> GameState::getObjectIds() const {
        auto ids = std::vector<std::string>(ecsManager->objectComponentMap.size());
        
        std::transform(objects.begin(), objects.end(), std::back_inserter(ids),
                       [](const GameObject& object) { return object.getId(); });
        
        return ids;
    }
    
    std::vector<std::string> GameState::getPlayerIds() const {
        std::vector<std::string> ids = std::vector<std::string>(ecsManager->objectComponentMap.size());
        
        std::transform(players.begin(), players.end(), std::back_inserter(ids),
                       [](const GamePlayer& player) { return player.getId(); });
        
        return ids;
    }
    
    size_t GameState::getObjectCount() const {
        return objects.size();
    }
    
    size_t GameState::getPlayerCount() const {
        return players.size();
    }
    
    std::vector<std::string> GameState::getComponentIds(const GameObject& obj) const {
        return getObjectComponentIds(obj.getId());
    }
    
    std::vector<std::string> GameState::getComponentIds(const GamePlayer& player) const {
        return getPlayerComponentIds(player.getId());
    }
    
    std::vector<std::string> GameState::getObjectComponentIds(const std::string& objId) const {
        assert(ecsManager != nullptr);
        
        if (ecsManager->objectComponentMap.count(objId)) {
            auto ids = std::vector<std::string>(players.size());
            std::transform(players.begin(), players.end(), std::back_inserter(ids),
                           [](const GamePlayer& player) { return player.getId(); });
            
            return ids;
        }

        throw std::invalid_argument("Object of ID " + objId + " not found in game");
    }
    
    std::vector<std::string> GameState::getPlayerComponentIds(const std::string& playerId) const {
        assert(ecsManager != nullptr);
        
        if (ecsManager->playerComponentMap.count(playerId)) {
            std::vector<std::string> ids = std::vector<std::string>(objects.size());
            std::transform(objects.begin(), objects.end(), std::back_inserter(ids),
                           [](const GameObject& object) { return object.getId(); });
            
            return ids;
        }

        throw std::invalid_argument("Player of ID " + playerId + " not found in game");
    }
    
    ObjectComponent& GameState::getComponent(const GameObject& object, const std::string& componentId) {
        return getObjectComponent(object.getId(), componentId);
    }
    
    PlayerComponent& GameState::getComponent(const GamePlayer& player, const std::string& componentId) {
        return getPlayerComponent(player.getId(), componentId);
    }

    ObjectComponent& GameState::getObjectComponent(const std::string& objId, const std::string& componentId) {
        if (!ecsManager->hasObject(objId)) {
            throw std::invalid_argument("Object does not exist or does not have any components");
        }
        
        ObjectComponent* component = ecsManager->getObjectComponent(objId, componentId);
        if (component == nullptr) {
            throw std::invalid_argument("Component of type ID " + componentId + " not found on object " + objId);
        }
        
        return *component;
    }
    
    PlayerComponent& GameState::getPlayerComponent(const std::string& playerId, const std::string& componentId) {
        if (!ecsManager->hasObject(playerId)) {
            throw std::invalid_argument("Player does not exist or does not have any components");
        }
        
        PlayerComponent* component = ecsManager->getPlayerComponent(playerId, componentId);
        if (component == nullptr) {
            throw std::invalid_argument("Component of type ID " + componentId + " not found on player " + playerId);
        }
        
        return *component;
    }
    
    void GameState::attachComponent(const GameObject& object, const ObjectComponent& component) {
        attachObjectComponent(object.getId(), component);
    }
    
    void GameState::attachComponent(const GamePlayer& player, const PlayerComponent& component) {
        attachPlayerComponent(player.getId(), component);
    }
    
    void GameState::attachObjectComponent(const std::string& objId, const ObjectComponent& component) {
        ecsManager->attachObjectComponent(objId, component.clone());
    }
    
    void GameState::attachPlayerComponent(const std::string& playerId, const PlayerComponent& component) {
        ecsManager->attachPlayerComponent(playerId, component.clone());
    }
    
    void GameState::removeComponent(const GameObject& object, const std::string& componentId) {
        removeObjectComponent(object.getId(), componentId);
    }
    
    void GameState::removeComponent(const GamePlayer& player, const std::string& componentId) {
        removePlayerComponent(player.getId(), componentId);
    }
    
    void GameState::removeObjectComponent(const std::string& objId, const std::string& componentId) {
        ecsManager->removeObjectComponent(objId, componentId);
    }
    
    void GameState::removePlayerComponent(const std::string& playerId, const std::string& componentId) {
        ecsManager->removePlayerComponent(playerId, componentId);
    }
    
    bool GameState::hasComponent(const GameObject& object, const std::string& componentId) const {
        return hasObjectComponent(object.getId(), componentId);
    }
    
    bool GameState::hasComponent(const GamePlayer& player, const std::string& componentId) const {
        return hasObjectComponent(player.getId(), componentId);
    }
    
    bool GameState::hasObjectComponent(const std::string& objId, const std::string& componentId) const {
        const std::vector<ObjectComponent*> components = ecsManager->getObjectComponents(objId);
        
        return std::any_of(components.begin(), components.end(),
                           [&componentId](const ObjectComponent* component) -> bool {
                               assert(component != nullptr);
                               
                               return component->getStrippedId() == componentId ||
                                      component->getTypeId() == componentId;
                           });
    }
    
    bool GameState::hasPlayerComponent(const std::string& playerId, const std::string& componentId) const {
        const std::vector<PlayerComponent*> components = ecsManager->getPlayerComponents(playerId);
        
        return std::any_of(components.begin(), components.end(),
                           [&componentId](const PlayerComponent* component) -> bool {
                               assert(component != nullptr);
                               
                               return component->getStrippedId() == componentId ||
                                      component->getTypeId() == componentId;
                           });
    }
    
    void GameState::addSystem(System* system) {
        ecsManager->addSystem(system);
    }
    
    GameObject& GameState::createObject(const math::Vector2& location, const ObjectPrefab& prefab) {
        objects.emplace_back(prefab.prefabId + std::to_string(latestObjectId++), location);
        
        GameObject& obj = objects.back();
        
        for (const ObjectComponent* component : prefab.components) {
            attachComponent(obj, *component);
        }
        
        return obj;
    }
    
    GamePlayer& GameState::addPlayer(const PlayerPrefab& prefab) {
        players.emplace_back(prefab.prefabId + std::to_string(objects.size()), objects.size());
        
        GamePlayer& player = players.back();
        
        for (const PlayerComponent* component : prefab.components) {
            attachComponent(player, *component);
        }
        
        return player;
    }

    void GameState::removeObject(const std::string& objId) {
        const auto it = std::remove_if(objects.begin(), objects.end(), [&objId](const GameObject& obj) -> bool {
            return obj.getId() == objId;
        });

        objects.erase(it);

        ecsManager
    }

    void GameState::removePlayer(const std::string& playerId) {

    }
    
    const std::string& GameState::getId() const {
        return id;
    }
    
    std::string GameState::getQualifiedId() const {
        return id + "~" + std::to_string(currentTurn);
    }
    
    PlayerHandle GameState::asHandle(const GamePlayer& player) {
        return game->asHandle(player);
    }
    
    ObjectHandle GameState::asHandle(const GameObject& object) {
        return game->asHandle(object);
    }
    
    PlayerComponentHandle GameState::asHandle(const std::string& owner, const PlayerComponent& component) {
        return game->asHandle(owner, component);
    }
    
    ObjectComponentHandle GameState::asHandle(const std::string& owner, const ObjectComponent& component) {
        return game->asHandle(owner, component);
    }
    
    GameState::~GameState() {
        delete ecsManager;
    }
}
