#include "limited_component.h"
#include "chococaker/name_space.h"

namespace ccaker {
    const wzc::NamespacedKey LimitedComponent::ID(NAMESPACE, "limited_component");

    LimitedComponent::LimitedComponent(uint16_t turnsLeft)
            : turnsLeft(turnsLeft) {}
    
    wzc::ObjectComponent* LimitedComponent::clone() const {
        return new LimitedComponent(turnsLeft);
    }
}
