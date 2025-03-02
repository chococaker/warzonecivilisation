#ifndef WARZONECIVILISATION_OBSTRUCTION_COMPONENT_H
#define WARZONECIVILISATION_OBSTRUCTION_COMPONENT_H

#include "wzc/ecs/component/entity/object_component.h"
#include <cstdint>

namespace ccaker {
struct ObstructionComponent final :  wzc::ObjectComponent {
        explicit ObstructionComponent(uint16_t size);
        
        [[nodiscard]] ObjectComponent* clone() const override;
        
        uint16_t size;
        
        static const std::string ID;
        const std::string& getTypeId() const override {
            return ID;
        }
    };
}


#endif //WARZONECIVILISATION_OBSTRUCTION_COMPONENT_H
