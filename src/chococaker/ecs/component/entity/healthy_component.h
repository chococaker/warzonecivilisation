#pragma once

#include <cstdint>
#include "wzc/ecs/component/entity/object_component.h"

namespace ccaker {
    struct HealthyComponent final : wzc::ObjectComponent {
        explicit HealthyComponent(uint16_t maxHealth);
        
        HealthyComponent(uint16_t maxHealth,
                         uint16_t health);
        
        [[nodiscard]] uint16_t getHealth() const;
        
        [[nodiscard]] bool isDead() const;
        
        void damage(uint16_t amount);
        
        void heal(uint16_t amount);
        
        [[nodiscard]] ObjectComponent* clone() const override;
        
        uint16_t maxHealth;
        
        static const std::string ID;
        
        const std::string& getTypeId() const override {
            return ID;
        }
    
    private:
        uint16_t health;
    };
}
