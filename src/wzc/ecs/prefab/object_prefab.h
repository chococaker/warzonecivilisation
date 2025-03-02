#ifndef WARZONECIVILISATION_OBJECT_PREFAB_H
#define WARZONECIVILISATION_OBJECT_PREFAB_H

#include <string>
#include <vector>
#include <cstdint>

namespace wzc {
    struct ComponentManager;
    struct ObjectComponent;
    struct GameState;
    struct Game;
    
    struct ObjectPrefab {
        ObjectPrefab(Game* game,
                     const std::string& basePrefabId,
                     const std::vector<ObjectComponent>& components);
        
        std::string getOriginalId() const;
        const std::string& getModifiedId() const;
    private:
        mutable uint16_t instance = 0;
        
        uint32_t nextRandId = 0x3a406bf3; //smth random
        
        Game* game;
        
        const std::string prefabId;
        std::vector<const ObjectComponent*> components;
        
        friend GameState;
    };
}


#endif //WARZONECIVILISATION_OBJECT_PREFAB_H
