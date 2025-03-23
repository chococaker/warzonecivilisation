#pragma once

#include "wzc/ecs/component/entity/object_component.h"
#include "chococaker/defs/inventory_def.h"

#include <unordered_map>

namespace ccaker {
struct CostlyPerTurnComponent final :  wzc::ObjectComponent {
        explicit CostlyPerTurnComponent(const Inventory& costPerTurn = Inventory());
        
        [[nodiscard]] ObjectComponent* clone() const override;
        
        Inventory costPerTurn;
        
        static const wzc::NamespacedKey ID;
        
        const wzc::NamespacedKey& getTypeKey() const override {
            return ID;
        }
    };
}
