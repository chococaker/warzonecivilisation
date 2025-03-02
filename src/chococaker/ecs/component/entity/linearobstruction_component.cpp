#include "linearobstruction_component.h"

namespace ccaker {
    const std::string LinearObstructionComponent::ID = "ocho@linear_obstruction";

    LinearObstructionComponent::LinearObstructionComponent(const wzc::math::Vector2& endpoint, uint16_t width)
            : endpoint(endpoint), width(width) {}
    
    wzc::ObjectComponent* LinearObstructionComponent::clone() const {
        return new LinearObstructionComponent(endpoint, width);
    }
}
