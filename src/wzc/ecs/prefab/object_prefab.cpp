#include "object_prefab.h"

#include "wzc/ecs/component/entity/object_component.h"
#include "wzc/game_state.h"
#include "wzc/game.h"
#include "mtwister/mtwister.h"

namespace wzc {
    ObjectPrefab::ObjectPrefab(Game* game,
                               const std::string& basePrefabId,
                               const std::vector<ObjectComponent>& components)
            : game(game), prefabId(basePrefabId + "_" + std::to_string(nextRandId)) {
        this->components = std::vector<const ObjectComponent*>();
        for (const ObjectComponent& component : components) {
            this->components.push_back(component.clone());
        }
        
        nextRandId = genRandLong(game->getRand());
    }
    
    std::string ObjectPrefab::getOriginalId() const {
        return prefabId.substr(0, prefabId.find_last_of('_'));
    }
    
    const std::string& ObjectPrefab::getModifiedId() const {
        return prefabId;
    }

    const std::vector<const ObjectComponent*>& ObjectPrefab::getComponents() const {
        return components;
    }
}
