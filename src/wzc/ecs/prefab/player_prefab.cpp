#include "player_prefab.h"

#include "wzc/ecs/component/player/player_component.h"
#include "wzc/game_state.h"
#include "wzc/game_player.h"

namespace wzc {
    PlayerPrefab::PlayerPrefab(std::string prefabId, const std::vector<PlayerComponent>& components)
            : prefabId(std::move(prefabId) + "@") {
        this->components = std::vector<const PlayerComponent*>();
        
        for (const PlayerComponent& component : components) {
            this->components.push_back(component.clone());
        }
    }
}
