#include "bought_component.h"

namespace ccaker {
    const std::string BoughtComponent::ID = "ocho@bought";

    BoughtComponent::BoughtComponent(const Inventory& cost)
            : cost(cost) {}
    
    wzc::ObjectComponent* BoughtComponent::clone() const {
        return new BoughtComponent(cost);
    }
}
