#include "health_event.h"
#include "wzc/game_state.h"

namespace ccaker {
    const std::string HealEvent::ID = "echo@heal";
    const std::string DamageEvent::ID = "echo@damage";
    const std::string OverhealEventError::ID = "rcho@overheal";
    
    HealEvent::HealEvent(const uint16_t amountHeal,
                         const wzc::ObjectHandle& healedObj)
            : amountHeal(amountHeal), healedObj(healedObj) { }
}
