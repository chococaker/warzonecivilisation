#pragma once

#include "wzc/ecs/component/entity/object_component.h"
#include "chococaker/defs/inventory_def.h"

#include <unordered_map>

namespace ccaker {
    struct HealableComponent final :  wzc::ObjectComponent {
        explicit HealableComponent(Inventory fullHealCost);
        
        [[nodiscard]] ObjectComponent* clone() const override;
        
        Inventory fullHealCost;
        
        static const wzc::NamespacedKey ID;
        
        const wzc::NamespacedKey& getTypeKey() const override {
            return ID;
        }
    };
}

