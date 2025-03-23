#include "attacker_component.h"
#include "chococaker/name_space.h"

namespace ccaker {
    const wzc::NamespacedKey AttackerComponent::ID(NAMESPACE, "attacker_component");

    AttackerComponent::AttackerComponent(const uint16_t range) : range(range), hasAttacked(false) {}

    AttackerComponent::AttackerComponent(const uint16_t range, const bool hasAttacked) : range(range), hasAttacked(hasAttacked) {}
    
    wzc::ObjectComponent* AttackerComponent::clone() const {
        return new AttackerComponent(range, hasAttacked);
    }
}
