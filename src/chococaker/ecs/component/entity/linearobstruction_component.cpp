#include "linearobstruction_component.h"
#include "chococaker/name_space.h"

namespace ccaker {
    const wzc::NamespacedKey LinearObstructionComponent::ID(NAMESPACE, "linearobstruction_component");

    LinearObstructionComponent::LinearObstructionComponent(const wzc::math::Point2D& endpoint, uint16_t width)
            : endpoint(endpoint), width(width) {}
    
    wzc::ObjectComponent* LinearObstructionComponent::clone() const {
        return new LinearObstructionComponent(endpoint, width);
    }
}
