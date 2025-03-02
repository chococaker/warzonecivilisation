#ifndef WARZONECIVILISATION_LIMITED_COMPONENT_H
#define WARZONECIVILISATION_LIMITED_COMPONENT_H

#include "wzc/ecs/component/entity/object_component.h"
#include <cstdint>

// This component makes an occupant only exist for a limited amount of turns
namespace ccaker {
    struct LimitedComponent final :  wzc::ObjectComponent {
        explicit LimitedComponent(uint16_t turnsLeft);
        
        [[nodiscard]] ObjectComponent* clone() const override;
        
        uint16_t turnsLeft;
        
        static const std::string ID;
        
        const std::string& getTypeId() const override {
            return ID;
        }
    };
}


#endif //WARZONECIVILISATION_LIMITED_COMPONENT_H
