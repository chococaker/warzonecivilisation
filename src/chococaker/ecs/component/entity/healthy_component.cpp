#include "healthy_component.h"
#include <algorithm>

namespace ccaker {
    const std::string HealthyComponent::ID = "ocho@healthy";
    
    HealthyComponent::HealthyComponent(const uint16_t maxHealth)
            : HealthyComponent(maxHealth, maxHealth) {}
    
    HealthyComponent::HealthyComponent(const uint16_t maxHealth,
                                       const uint16_t health)
            : maxHealth(maxHealth),
              health(health) {}
    
    uint16_t HealthyComponent::getHealth() const {
        return health;
    }
    
    bool HealthyComponent::isDead() const {
        return health == 0;
    }
    
    void HealthyComponent::damage(const uint16_t amount) {
        health -= std::clamp<uint16_t>(amount, 0, health);
    }
    
    void HealthyComponent::heal(const uint16_t amount) {
        health = std::clamp<uint16_t>(health + amount, health, maxHealth);
    }
    
    wzc::ObjectComponent* HealthyComponent::clone() const {
        return new HealthyComponent(maxHealth, health);
    }
}
