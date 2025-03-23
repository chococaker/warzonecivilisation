#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace wzc {
    struct PlayerComponent;
    struct GameState;
    
    struct PlayerPrefab {
        PlayerPrefab(std::string prefabId, const std::vector<PlayerComponent>& components);

        const std::vector<const PlayerComponent*>& getComponents() const;

    private:
        mutable uint16_t instance = 0;
        
        const std::string prefabId;
        std::vector<const PlayerComponent*> components;
        
        friend GameState;
    };
}
