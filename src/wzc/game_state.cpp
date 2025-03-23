#include "game_state.h"
#include "game.h"
#include "wzc/game_player.h"
#include "wzc/game_object.h"
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
            : typeMap(tileTypeMap),
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
        // TODO: clone components
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
    
    GameObject& GameState::getObject(const math::Point2D& location) {
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
        auto ids = std::vector<std::string>(objects.size());

        std::transform(objects.begin(), objects.end(), std::back_inserter(ids),
                       [](const GameObject& object) { return object.getId(); });
        
        return ids;
    }
    
    std::vector<std::string> GameState::getPlayerIds() const {
        std::vector<std::string> ids = std::vector<std::string>(players.size());
        
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
    
    GameObject& GameState::createObject(const math::Point2D& location, const ObjectPrefab& prefab) {
        objects.emplace_back(prefab.prefabId + std::to_string(latestObjectId++), location);
        
        GameObject& obj = objects.back();
        
        for (const ObjectComponent* component : prefab.components) {
            obj.attachComponent(*component);
        }
        
        return obj;
    }
    
    GamePlayer& GameState::addPlayer(const PlayerPrefab& prefab) {
        players.emplace_back(prefab.prefabId + std::to_string(objects.size()), objects.size());
        
        GamePlayer& player = players.back();
        
        for (const PlayerComponent* component : prefab.components) {
            player.attachComponent(*component);
        }
        
        return player;
    }

    void GameState::removeObject(const std::string& objId) {
        const auto it = std::remove_if(objects.begin(), objects.end(), [&objId](const GameObject& obj) -> bool {
            return obj.getId() == objId;
        });

        objects.erase(it);
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
    
    PlayerComponentHandle GameState::asHandle(const GamePlayer& owner, const PlayerComponent& component) {
        return game->asHandle(owner, component);
    }
    
    ObjectComponentHandle GameState::asHandle(const GameObject& owner, const ObjectComponent& component) {
        return game->asHandle(owner, component);
    }

    std::vector<GamePlayer*> GameState::getPlayersWith(const NamespacedKey& componentId) {
        std::vector<GamePlayer*> result;

        for (GamePlayer& player : players) {
            if (player.hasComponent(componentId)) result.emplace_back(&player);
        }

        return result;
    }

    std::vector<GameObject*> GameState::getObjectsWith(const NamespacedKey& componentId) {
        std::vector<GameObject*> result;

        for (GameObject& object : objects) {
            if (object.hasComponent(componentId)) result.emplace_back(&object);
        }

        return result;
    }
    
    GameState::~GameState() {

    }
}
