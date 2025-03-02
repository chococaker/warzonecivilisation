#include "attacker_component.h"
#include <stdexcept>

namespace ccaker {
    const std::string AttackerComponent::ID = "ocho@attacker";

    AttackerComponent::AttackerComponent(const uint16_t range) : range(range), hasAttacked(false) {}

    AttackerComponent::AttackerComponent(const uint16_t range, const bool hasAttacked) : range(range), hasAttacked(hasAttacked) {}
    
    wzc::ObjectComponent* AttackerComponent::clone() const {
        return new AttackerComponent(range, hasAttacked);
    }
}
