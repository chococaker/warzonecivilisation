#ifndef WARZONECIVILISATION_RANGEDCREATION_COMPONENT_H
#define WARZONECIVILISATION_RANGEDCREATION_COMPONENT_H

#include <cstdint>
#include "wzc/ecs/component/entity/object_component.h"

namespace ccaker {
    struct RangedCreationComponent final :  wzc::ObjectComponent {
        explicit RangedCreationComponent(uint16_t radius);
        
        [[nodiscard]] ObjectComponent* clone() const override;
        
        uint16_t radius;
        
        static const std::string ID;
        
        const std::string& getTypeId() const override {
            return ID;
        }
    };
}


#endif //WARZONECIVILISATION_RANGEDCREATION_COMPONENT_H
