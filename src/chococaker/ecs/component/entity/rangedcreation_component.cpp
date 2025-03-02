#include "rangedcreation_component.h"

namespace ccaker {
    const std::string RangedCreationComponent::ID = "ocho@ranged_creation";

    RangedCreationComponent::RangedCreationComponent(uint16_t radius)
            : radius(radius) {}
    
    wzc::ObjectComponent* RangedCreationComponent::clone() const {
        return new RangedCreationComponent(radius);
    }
}
