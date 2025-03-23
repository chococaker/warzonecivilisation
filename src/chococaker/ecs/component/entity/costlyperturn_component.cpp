#include "costlyperturn_component.h"

#include "chococaker/name_space.h"

namespace ccaker {
    const wzc::NamespacedKey CostlyPerTurnComponent::ID(NAMESPACE, "costlyperturn_component");

    CostlyPerTurnComponent::CostlyPerTurnComponent(const Inventory& costPerTurn)
            : costPerTurn(costPerTurn) {}
    
    wzc::ObjectComponent* CostlyPerTurnComponent::clone() const {
        return new CostlyPerTurnComponent(costPerTurn);
    }
}
