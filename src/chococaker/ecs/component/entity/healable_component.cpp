#include "healable_component.h"

#include <utility>

namespace ccaker {
    const std::string HealableComponent::ID = "ocho@healable";
    
    HealableComponent::HealableComponent(Inventory fullHealCost)
            : fullHealCost(std::move(fullHealCost)) { }
    
    wzc::ObjectComponent* HealableComponent::clone() const {
        return new HealableComponent(fullHealCost);
    }
}
