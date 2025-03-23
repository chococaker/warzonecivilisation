#include "health_event.h"

#include "chococaker/name_space.h"

#include "wzc/game_state.h"

namespace ccaker {
    const wzc::NamespacedKey HealEvent::ID(NAMESPACE, "heal_event");
    const wzc::NamespacedKey DamageEvent::ID(NAMESPACE, "damage_event");
    const wzc::NamespacedKey OverhealEventError::ID(NAMESPACE, "overheal_event_error");
    
    HealEvent::HealEvent(const uint16_t amountHeal,
                         const wzc::ObjectHandle& healedObj)
            : amountHeal(amountHeal), healedObj(healedObj) { }
}
