#pragma once

#include "wzc/ecs/component/entity/object_component.h"

// If all phylactery components of a player are destroyed, the player dies
namespace ccaker {
    struct PhylacteryComponent final :  wzc::ObjectComponent {
        [[nodiscard]] ObjectComponent* clone() const override;
        
        static const wzc::NamespacedKey ID;
        
        const wzc::NamespacedKey& getTypeKey() const override {
            return ID;
        }
    };
}
