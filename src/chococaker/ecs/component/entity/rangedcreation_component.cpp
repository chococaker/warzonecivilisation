#include "rangedcreation_component.h"
#include "chococaker/name_space.h"

namespace ccaker {
    const wzc::NamespacedKey RangedCreationComponent::ID(NAMESPACE, "ranged_creation_component");

    RangedCreationComponent::RangedCreationComponent(uint16_t radius)
            : radius(radius) {}
    
    wzc::ObjectComponent* RangedCreationComponent::clone() const {
        return new RangedCreationComponent(radius);
    }
}
