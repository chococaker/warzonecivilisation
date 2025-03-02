#include "costlyperturn_component.h"

namespace ccaker {
    const std::string CostlyPerTurnComponent::ID = "ocho@costly_per_turn";

    CostlyPerTurnComponent::CostlyPerTurnComponent(const Inventory& costPerTurn)
            : costPerTurn(costPerTurn) {}
    
    wzc::ObjectComponent* CostlyPerTurnComponent::clone() const {
        return new CostlyPerTurnComponent(costPerTurn);
    }
}
