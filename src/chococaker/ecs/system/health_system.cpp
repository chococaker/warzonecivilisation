#include "health_system.h"

#include "chococaker/name_space.h"
#include "chococaker/ecs/system/event/health_event.h"
#include "wzc/ecs/system/event/end_event.h"
#include "chococaker/ecs/system/event/generic_errors.h"
#include "wzc/game_state.h"
#include "chococaker/ecs/component/entity/attacker_component.h"
#include "chococaker/ecs/component/entity/healable_component.h"
#include "chococaker/ecs/component/entity/healthy_component.h"
#include "chococaker/ecs/component/entity/owned_component.h"
#include "chococaker/ecs/component/player/inventory_component.h"
#include "chococaker/util/event_error_util.h"

#include <cmath>

namespace ccaker {
    const wzc::NamespacedKey HealthSystem::ID(NAMESPACE, "health_system");

    void attack(wzc::Event* ev, wzc::GameState* game) {
        auto* e = dynamic_cast<DamageEvent*>(ev);

        wzc::GameObject& attackerObj = e->attacker.get();
        wzc::GameObject& attackedObj = e->attacked.get();
        const uint16_t damage = e->damage;

        auto& healthyComponent = getComponent<HealthyComponent>(attackedObj);

        auto& attackerComponent = getComponent<AttackerComponent>(attackerObj);

        if (double distance = attackerObj.getLocation().getDistance(attackedObj.getLocation()); distance < attackerComponent.range) {
            throw OutOfRangeError(attackerObj.getId(), attackerComponent.range, distance);
        }

        attackerComponent.hasAttacked = true;

        healthyComponent.damage(damage);
    }

    void heal(wzc::Event* ev, wzc::GameState* game) {
        HealEvent* e = dynamic_cast<HealEvent*>(ev);
        wzc::GameObject& healedObj = e->healedObj.get();

        HealthyComponent& healthyComponent = getComponent<HealthyComponent>(healedObj);
        HealableComponent& healableComponent = getComponent<HealableComponent>(healedObj);
        OwnedComponent& ownedComponent = getComponent<OwnedComponent>(healedObj);

        InventoryComponent& inventoryComponent = getComponent<InventoryComponent>(ownedComponent.getOwner().get());

        const double healPercent = static_cast<double>(e->amountHeal) / healthyComponent.maxHealth;

        for (const auto& [costMaterialId, fullHealCost]: healableComponent.fullHealCost) {
            uint32_t cost = static_cast<uint32_t>(std::ceil(fullHealCost * healPercent));

            uint32_t amountHad = inventoryComponent.getMaterial(costMaterialId);

            if (amountHad < cost)
                throw TooExpensiveError(costMaterialId, amountHad, cost);

            inventoryComponent.reduceMaterial(costMaterialId, cost);
        }

        healthyComponent.heal(e->amountHeal);
    }

    // perform cleanup (remove dead objects)
    void fin(wzc::Event* ev, wzc::GameState* game) {
        // look for objects
        for (const std::string& objId: game->getObjectIds()) {
            if (wzc::GameObject& object = game->getObject(objId); object.hasComponent(HealEvent::ID)) {
                object.markedForDestruction = true;
            }
        }
    }

    HealthSystem::HealthSystem()
        : System(ID, {
                     {HealEvent::ID, heal, false},
                     {DamageEvent::ID, attack, false},
                     {wzc::EndEvent::ID, fin, false}
                 }) {
    }
}
