#include "healable_component.h"

#include "chococaker/name_space.h"

#include <utility>

namespace ccaker {
    const wzc::NamespacedKey HealableComponent::ID(NAMESPACE, "healable_component");
    
    HealableComponent::HealableComponent(Inventory fullHealCost)
            : fullHealCost(std::move(fullHealCost)) { }
    
    wzc::ObjectComponent* HealableComponent::clone() const {
        return new HealableComponent(fullHealCost);
    }
}
