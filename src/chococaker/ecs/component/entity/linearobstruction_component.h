#ifndef WARZONECIVILISATION_LINEAROBSTRUCTION_COMPONENT_H
#define WARZONECIVILISATION_LINEAROBSTRUCTION_COMPONENT_H

#include "wzc/ecs/component/entity/object_component.h"
#include "wzc/math/point2d.h"

namespace ccaker {
    struct LinearObstructionComponent final : wzc::ObjectComponent {
        LinearObstructionComponent(const wzc::math::Point2D& endpoint, uint16_t width);
        
        [[nodiscard]] ObjectComponent* clone() const override;
        
        wzc::math::Point2D endpoint;
        uint16_t width;
        
        static const std::string ID;
        
        const std::string& getTypeId() const override {
            return ID;
        }
    };
}


#endif //WARZONECIVILISATION_LINEAROBSTRUCTION_COMPONENT_H
