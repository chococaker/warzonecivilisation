#ifndef WARZONECIVILISATION_GAME_STATE_H
#define WARZONECIVILISATION_GAME_STATE_H

#include <memory>
#include <stdexcept>
#include <vector>
#include "game_type_map.h"

#include "handle/player_handle.h"
#include "handle/object_handle.h"
#include "ecs/component/handle/player_component_handle.h"
#include "ecs/component/handle/object_component_handle.h"

struct tagMTRand;

namespace wzc {
    struct GamePlayer;
    struct GameObject;
    struct EcsManager;
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
        GameObject& getObject(const math::Vector2& location);
        GamePlayer& getPlayer(const std::string& playerId);
        
        bool hasPlayer(const std::string& playerId) const;
        bool hasObject(const std::string& objId) const;
        
        std::vector<std::string> getObjectIds() const;
        std::vector<std::string> getPlayerIds() const;
        
        size_t getObjectCount() const;
        size_t getPlayerCount() const;
        
        std::vector<std::string> getComponentIds(const GameObject& obj) const;
        std::vector<std::string> getComponentIds(const GamePlayer& player) const;
        std::vector<std::string> getObjectComponentIds(const std::string& objId) const;
        std::vector<std::string> getPlayerComponentIds(const std::string& playerId) const;
        
        ObjectComponent& getComponent(const GameObject& object, const std::string& componentId);
        PlayerComponent& getComponent(const GamePlayer& player, const std::string& componentId);
        ObjectComponent& getObjectComponent(const std::string& objId, const std::string& componentId);
        PlayerComponent& getPlayerComponent(const std::string& playerId, const std::string& componentId);
        
        void attachComponent(const GameObject& object, const ObjectComponent& component);
        void attachComponent(const GamePlayer& player, const PlayerComponent& component);
        void attachObjectComponent(const std::string& objId, const ObjectComponent& component);
        void attachPlayerComponent(const std::string& playerId, const PlayerComponent& component);
        
        void removeComponent(const GameObject& object, const std::string& componentId);
        void removeComponent(const GamePlayer& player, const std::string& componentId);
        void removeObjectComponent(const std::string& objId, const std::string& componentId);
        void removePlayerComponent(const std::string& playerId, const std::string& componentId);
        
        bool hasComponent(const GameObject& object, const std::string& componentId) const;
        bool hasComponent(const GamePlayer& player, const std::string& componentId) const;
        bool hasObjectComponent(const std::string& objId, const std::string& componentId) const;
        bool hasPlayerComponent(const std::string& playerId, const std::string& componentId) const;
        
        void addSystem(System* system); // takes ownership of system
        
        GameObject& createObject(const math::Vector2& location, const ObjectPrefab& prefab);
        GamePlayer& addPlayer(const PlayerPrefab& prefab);

        void removeObject(const std::string& objId);
        void removePlayer(const std::string& playerId);
        
        template<typename T>
        T& getObjectComponent(const std::string& objId);
        template<typename T>
        T& getPlayerComponent(const std::string& playerId);
        
        const std::string& getId() const;
        std::string getQualifiedId() const; // id~currentTurn
        
        PlayerHandle asHandle(const GamePlayer& player);
        ObjectHandle asHandle(const GameObject& object);
        PlayerComponentHandle asHandle(const std::string& owner, const PlayerComponent& component);
        ObjectComponentHandle asHandle(const std::string& owner, const ObjectComponent& component);
        
        ~GameState();
    private:
        EcsManager* ecsManager;
        
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
    
    template<typename T>
    T& GameState::getObjectComponent(const std::string& objId) {
        ObjectComponent& component = getObjectComponent(objId, T::ID);
        
        try {
            T& t = dynamic_cast<T&>(component);
            return t;
        } catch (const std::bad_cast&) {
            throw std::invalid_argument("Object component " + objId + " is not of the requested template type");
        }
    }
    
    template<typename T>
    T& GameState::getPlayerComponent(const std::string& playerId) {
        PlayerComponent& component = getPlayerComponent(playerId, T::ID);
        
        try {
            T& t = dynamic_cast<T&>(component);
            return t;
        } catch (const std::bad_cast&) {
            throw std::invalid_argument("Player component " + playerId + " is not of the requested template type");
        }
    }
}


#endif //WARZONECIVILISATION_GAME_STATE_H
