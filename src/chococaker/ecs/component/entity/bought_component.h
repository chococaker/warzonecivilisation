#ifndef WARZONECIVILISATION_BOUGHT_COMPONENT_H
#define WARZONECIVILISATION_BOUGHT_COMPONENT_H

#include <unordered_map>
#include <cstdint>
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


#endif //WARZONECIVILISATION_BOUGHT_COMPONENT_H
