#include "producer_component.h"

namespace ccaker {
    const std::string ProducerComponent::ID = "ocho@producer";

    ProducerComponent::ProducerComponent(const Inventory& productionPerTurn)
            : productionPerTurn(productionPerTurn) {}
    
    wzc::ObjectComponent* ProducerComponent::clone() const {
        return new ProducerComponent(productionPerTurn);
    }
}
