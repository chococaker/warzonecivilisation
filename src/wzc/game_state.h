#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

#include "game_object.h"
#include "game_player.h"
#include "game_type_map.h"

#include "handle/player_handle.h"
#include "handle/object_handle.h"
#include "ecs/component/handle/player_component_handle.h"
#include "ecs/component/handle/object_component_handle.h"

struct tagMTRand;

namespace wzc {
    struct GamePlayer;
    struct GameObject;
    struct ObjectComponent;
    struct PlayerComponent;
    struct Game;
    struct ObjectPrefab;
    struct PlayerPrefab;
    struct System;
    
    struct GameState {
        GameState(const TileTypeMap* tileTypeMap, tagMTRand* rand, int16_t latestObjectId, Game* game);
        GameState(const GameState& other);
        
        [[nodiscard]] size_t getCurrentTurn() const;
        
        [[nodiscard]] GamePlayer& getCurrentPlayer();
        [[nodiscard]] GamePlayer& getPlayerAt(size_t turn);
        
        GameObject& getObject(const std::string& objId);
        GameObject& getObject(const math::Point2D& location);
        GamePlayer& getPlayer(const std::string& playerId);
        
        bool hasPlayer(const std::string& playerId) const;
        bool hasObject(const std::string& objId) const;
        
        std::vector<std::string> getObjectIds() const;
        std::vector<std::string> getPlayerIds() const;
        
        size_t getObjectCount() const;
        size_t getPlayerCount() const;

        // takes ownership of system
        void addSystem(System* system);
        
        GameObject& createObject(const math::Point2D& location, const ObjectPrefab& prefab);
        GamePlayer& addPlayer(const PlayerPrefab& prefab);

        void removeObject(const std::string& objId);
        void removePlayer(const std::string& playerId);
        
        const std::string& getId() const;
        std::string getQualifiedId() const; // id~currentTurn
        
        PlayerHandle asHandle(const GamePlayer& player);
        ObjectHandle asHandle(const GameObject& object);
        PlayerComponentHandle asHandle(const GamePlayer& owner, const PlayerComponent& component);
        ObjectComponentHandle asHandle(const GameObject& owner, const ObjectComponent& component);

        std::vector<GamePlayer*> getPlayersWith(const NamespacedKey& componentId);
        std::vector<GameObject*> getObjectsWith(const NamespacedKey& componentId);

        ~GameState();
    private:
        std::vector<System*> systems;

        std::vector<GamePlayer> players;
        std::vector<GameObject> objects;
        
        const std::string id;
        
        const TileTypeMap* typeMap;
        size_t currentTurn;
        
        int16_t latestObjectId;
        
        tagMTRand* rand;
        
        Game* game;
        
        friend Game;
        friend struct PlayerComponentHandle;
        friend struct ObjectComponentHandle;
        friend struct PlayerHandle;
        friend struct ObjectHandle;
    };
}
