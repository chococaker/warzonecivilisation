#include "bought_component.h"
#include "chococaker/name_space.h"

namespace ccaker {
    const wzc::NamespacedKey BoughtComponent::ID(NAMESPACE, "bought_component");

    BoughtComponent::BoughtComponent(const Inventory& cost)
            : cost(cost) {}
    
    wzc::ObjectComponent* BoughtComponent::clone() const {
        return new BoughtComponent(cost);
    }
}
