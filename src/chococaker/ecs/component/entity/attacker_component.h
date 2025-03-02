#ifndef WARZONECIVILISATION_ATTACKER_COMPONENT_H
#define WARZONECIVILISATION_ATTACKER_COMPONENT_H

#include <cstdint>
#include "wzc/ecs/component/entity/object_component.h"

namespace ccaker {
    struct AttackerComponent final : wzc::ObjectComponent {
        explicit AttackerComponent(uint16_t range);
        AttackerComponent(uint16_t range, bool hasAttacked);
        
        [[nodiscard]] ObjectComponent* clone() const override;
        uint16_t range;
        
        bool hasAttacked;
        
        static const std::string ID;
        
        const std::string& getTypeId() const override {
            return ID;
        }
    };
}


#endif //WARZONECIVILISATION_ATTACKER_COMPONENT_H
