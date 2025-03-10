#ifndef WARZONECIVILISATION_HEALING_SYSTEM_H
#define WARZONECIVILISATION_HEALING_SYSTEM_H

#include "wzc/ecs/system/system.h"

namespace ccaker {
    struct HealthSystem final : wzc::System {
        HealthSystem();
        
        const std::string& getId() const override {
            return ID;
        }
        static const std::string ID;
    private:
        static const wzc::SystemHandler onHeal;
        static const wzc::SystemHandler onDamage;
    };
    
}

#endif // WARZONECIVILISATION_HEALING_SYSTEM_H
