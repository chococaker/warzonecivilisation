#ifndef WARZONECIVILISATION_HEALABLE_COMPONENT_H
#define WARZONECIVILISATION_HEALABLE_COMPONENT_H

#include "wzc/ecs/component/entity/object_component.h"
#include "chococaker/defs/inventory_def.h"

#include <unordered_map>
#include <cstdint>

namespace ccaker {
    struct HealableComponent final :  wzc::ObjectComponent {
        explicit HealableComponent(Inventory fullHealCost);
        
        [[nodiscard]] ObjectComponent* clone() const override;
        
        Inventory fullHealCost;
        
        static const std::string ID;
        
        const std::string& getTypeId() const override {
            return ID;
        }
    };
}


#endif //WARZONECIVILISATION_HEALABLE_COMPONENT_H
