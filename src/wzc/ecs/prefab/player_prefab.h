#ifndef WARZONECIVILISATION_PLAYER_PREFAB_H
#define WARZONECIVILISATION_PLAYER_PREFAB_H

#include <string>
#include <vector>
#include <cstdint>

namespace wzc {
    struct EcsManager;
    struct PlayerComponent;
    struct GameState;
    
    struct PlayerPrefab {
        PlayerPrefab(std::string prefabId, const std::vector<PlayerComponent>& components);
    private:
        mutable uint16_t instance = 0;
        
        const std::string prefabId;
        std::vector<const PlayerComponent*> components;
        
        friend GameState;
    };
}


#endif