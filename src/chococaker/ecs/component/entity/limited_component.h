#pragma once

#include "wzc/ecs/component/entity/object_component.h"
#include <cstdint>

// This component makes an occupant only exist for a limited amount of turns
namespace ccaker {
    struct LimitedComponent final :  wzc::ObjectComponent {
        explicit LimitedComponent(uint16_t turnsLeft);
        
        [[nodiscard]] ObjectComponent* clone() const override;
        
        uint16_t turnsLeft;
        
        static const wzc::NamespacedKey ID;
        
        const wzc::NamespacedKey& getTypeKey() const override {
            return ID;
        }
    };
}
