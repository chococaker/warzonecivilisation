#ifndef WARZONECIVILISATION_HEALTH_EVENT_H
#define WARZONECIVILISATION_HEALTH_EVENT_H

#include <string>
#include <cstdint>
#include "wzc/ecs/system/event/event.h"
#include "wzc/handle/object_handle.h"

namespace wzc {
    struct GameState;
    struct GamePlayer;
    struct GameObject;
}

namespace ccaker {
    struct HealEvent final : wzc::Event {
        HealEvent(wzc::GameState* game,
                  uint16_t amountHeal,
                  const wzc::ObjectHandle& healedObj);
        
        const std::string& getTypeId() const override {
            return ID;
        }
        
        static const std::string ID;
        
        uint16_t amountHeal;
        wzc::ObjectHandle healedObj;
    };
    
    struct DamageEvent final : wzc::Event {
        DamageEvent(wzc::GameState* game,
                    const uint16_t damage,
                    const wzc::ObjectHandle& attacker,
                    const wzc::ObjectHandle& attacked)
                : Event(game), damage(damage), attacker(attacker), attacked(attacked) { }
        
        const std::string& getTypeId() const override {
            return ID;
        }
        
        static const std::string ID;
        
        const uint16_t damage;
        const wzc::ObjectHandle& attacker;
        const wzc::ObjectHandle& attacked;
    };
    
    struct OverhealEventError : wzc::EventError {
        const std::string& getTypeId() const override {
            return ID;
        }
        
        static const std::string ID;
    };
}

#endif
