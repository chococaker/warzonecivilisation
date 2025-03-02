#ifndef WARZONECIVILISATION_COSTLYPERTURN_COMPONENT_H
#define WARZONECIVILISATION_COSTLYPERTURN_COMPONENT_H

#include "wzc/ecs/component/entity/object_component.h"
#include "chococaker/defs/inventory_def.h"

#include <unordered_map>
#include <cstdint>

namespace ccaker {
struct CostlyPerTurnComponent final :  wzc::ObjectComponent {
        explicit CostlyPerTurnComponent(const Inventory& costPerTurn = Inventory());
        
        [[nodiscard]] ObjectComponent* clone() const override;
        
        Inventory costPerTurn;
        
        static const std::string ID;
        
        const std::string& getTypeId() const override {
            return ID;
        }
    };
}


#endif //WARZONECIVILISATION_COSTLYPERTURN_COMPONENT_H
