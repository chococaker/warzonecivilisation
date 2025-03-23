#include "movable_component.h"
#include "chococaker/name_space.h"
#include <algorithm>
#include <stdexcept>

namespace ccaker {
    const wzc::NamespacedKey MovableComponent::ID(NAMESPACE, "movable_component");

    MovableComponent::MovableComponent(uint16_t maxDistancePerFullMove,
                                       const std::vector<uint8_t>& traversableTileTypes,
                                       double amountMovedThisTurn)
            : maxDistancePerFullMove(maxDistancePerFullMove),
              traversableTileTypes(traversableTileTypes),
              amountMovedThisTurn(amountMovedThisTurn) { }
    
    double MovableComponent::getAmountMovedThisTurn() const {
        return amountMovedThisTurn;
    }
    
    double MovableComponent::getAmountLeft() const {
        return maxDistancePerFullMove - amountMovedThisTurn;
    }
    
    bool MovableComponent::exceedsLimit(double more) const {
        return amountMovedThisTurn + more >= maxDistancePerFullMove;
    }
    
    void MovableComponent::addAmountMoved(double amount) {
        if (amount < 0) throw std::invalid_argument("amount (" + std::to_string(amount) + ") must be >= 0");
        amountMovedThisTurn = std::clamp<double>(amountMovedThisTurn + amount, 0, maxDistancePerFullMove);
    }
    
    void MovableComponent::subtractAmountMoved(double amount) {
        if (amount > 0) throw std::invalid_argument("amount (" + std::to_string(amount) + ") must be <= 0");
        amountMovedThisTurn = std::clamp<double>(amountMovedThisTurn - amount, 0, maxDistancePerFullMove);
    }
    
    void MovableComponent::resetAmountMoved() {
        amountMovedThisTurn = 0;
    }
    
    wzc::ObjectComponent* MovableComponent::clone() const {
        return new MovableComponent(maxDistancePerFullMove,
                                    traversableTileTypes,
                                    amountMovedThisTurn);
    }
}
