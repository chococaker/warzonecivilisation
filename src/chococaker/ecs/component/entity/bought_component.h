#pragma once

#include <unordered_map>
#include "chococaker/defs/inventory_def.h"
#include "wzc/ecs/component/entity/object_component.h"

namespace ccaker {
    struct BoughtComponent final :  wzc::ObjectComponent {
        explicit BoughtComponent(const Inventory& cost);
        
        [[nodiscard]] ObjectComponent* clone() const override;
        
        const Inventory cost;
        
        static const std::string ID;
        
        const std::string& getTypeId() const override {
            return ID;
        }
    };
}
