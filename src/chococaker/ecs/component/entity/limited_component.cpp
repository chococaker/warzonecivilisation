#include "limited_component.h"

namespace ccaker {
    const std::string LimitedComponent::ID = "ocho@limited";

    LimitedComponent::LimitedComponent(uint16_t turnsLeft)
            : turnsLeft(turnsLeft) {}
    
    wzc::ObjectComponent* LimitedComponent::clone() const {
        return new LimitedComponent(turnsLeft);
    }
}
