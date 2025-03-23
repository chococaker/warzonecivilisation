#pragma once

#include <unordered_map>
#include "chococaker/defs/inventory_def.h"
#include "wzc/ecs/component/entity/object_component.h"

namespace ccaker {
    struct BoughtComponent final :  wzc::ObjectComponent {
        explicit BoughtComponent(const Inventory& cost);
        
        [[nodiscard]] ObjectComponent* clone() const override;
        
        const Inventory cost;
        
        static const wzc::NamespacedKey ID;
        
        const wzc::NamespacedKey& getTypeKey() const override {
            return ID;
        }
    };
}
