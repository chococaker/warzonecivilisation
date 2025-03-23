#pragma once

#include <string>
#include <cstdint>
#include "wzc/ecs/system/event/event.h"
#include "wzc/handle/object_handle.h"

namespace ccaker {
    struct HealEvent final : wzc::Event {
        HealEvent(uint16_t amountHeal,
                  const wzc::ObjectHandle& healedObj);
        
        const wzc::NamespacedKey& getTypeKey() const override {
            return ID;
        }
        
        static const wzc::NamespacedKey ID;
        
        uint16_t amountHeal;
        wzc::ObjectHandle healedObj;
    };
    
    struct DamageEvent final : wzc::Event {
        DamageEvent(const uint16_t damage,
                    const wzc::ObjectHandle& attacker,
                    const wzc::ObjectHandle& attacked)
                : damage(damage), attacker(attacker), attacked(attacked) { }
        
        const wzc::NamespacedKey& getTypeKey() const override {
            return ID;
        }
        
        static const wzc::NamespacedKey ID;
        
        const uint16_t damage;
        const wzc::ObjectHandle& attacker;
        const wzc::ObjectHandle& attacked;
    };
    
    struct OverhealEventError final : wzc::EventError {
        const wzc::NamespacedKey& getTypeKey() const override {
            return ID;
        }
        
        static const wzc::NamespacedKey ID;
    };
}
