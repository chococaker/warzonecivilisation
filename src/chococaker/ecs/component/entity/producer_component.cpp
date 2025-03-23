#include "producer_component.h"
#include "chococaker/name_space.h"

namespace ccaker {
    const wzc::NamespacedKey ProducerComponent::ID(NAMESPACE, "producer_component");

    ProducerComponent::ProducerComponent(const Inventory& productionPerTurn)
            : productionPerTurn(productionPerTurn) {}
    
    wzc::ObjectComponent* ProducerComponent::clone() const {
        return new ProducerComponent(productionPerTurn);
    }
}
