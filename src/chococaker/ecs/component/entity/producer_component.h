#pragma once

#include "wzc/ecs/component/entity/object_component.h"
#include "chococaker/defs/inventory_def.h"

namespace ccaker {
struct ProducerComponent final :  wzc::ObjectComponent {
        explicit ProducerComponent(const Inventory& productionPerTurn);
        
        [[nodiscard]] ObjectComponent* clone() const override;
        
        Inventory productionPerTurn;
        
        static const std::string ID;
        const std::string& getTypeId() const override {
            return ID;
        }
    };
}
