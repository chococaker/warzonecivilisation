#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace wzc {
    struct ObjectComponent;
    struct GameState;
    struct Game;
    
    struct ObjectPrefab {
        ObjectPrefab(Game* game,
                     const std::string& basePrefabId,
                     const std::vector<ObjectComponent>& components);
        
        std::string getOriginalId() const;
        const std::string& getModifiedId() const;

        const std::vector<const ObjectComponent*>& getComponents() const;

    private:
        mutable uint16_t instance = 0;
        
        uint32_t nextRandId = 0x3a406bf3; //smth random
        
        Game* game;
        
        const std::string prefabId;
        std::vector<const ObjectComponent*> components;
        
        friend GameState;
    };
}
