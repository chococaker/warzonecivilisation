#pragma once

#include "wzc/ecs/system/system.h"

namespace ccaker {
    struct HealthSystem final : wzc::System {
        HealthSystem();
        
        const wzc::NamespacedKey& getKey() const override {
            return ID;
        }
        static const wzc::NamespacedKey ID;
    private:
        static const wzc::SystemHandler onHeal;
        static const wzc::SystemHandler onDamage;
    };
    
}
