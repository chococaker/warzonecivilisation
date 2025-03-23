#pragma once

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
