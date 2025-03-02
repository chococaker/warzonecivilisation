#include "health_system.h"

#include "chococaker/ecs/system/event/health_event.h"
#include "chococaker/ecs/system/event/generic_errors.h"
#include "wzc/game_state.h"
#include "chococaker/ecs/component/entity/attacker_component.h"
#include "chococaker/ecs/component/entity/healable_component.h"
#include "chococaker/ecs/component/entity/healthy_component.h"
#include "chococaker/ecs/component/entity/owned_component.h"
#include "chococaker/ecs/component/player/inventory_component.h"
#include "chococaker/util/event_error_util.h"

#include <cmath>

#include "wzc/ecs/system/event/end_event.h"

namespace ccaker {
    const std::string HealthSystem::ID = "scho@health";

    void attack(wzc::Event* ev) {
        auto* e = dynamic_cast<DamageEvent*>(ev);

        wzc::GameState* game = e->game;
        const wzc::GameObject& attackerObj = e->attacker.get();
        const wzc::GameObject& attackedObj = e->attacked.get();
        const uint16_t damage = e->damage;

        auto& healthyComponent = getComponent<HealthyComponent>(game,
                                                                attackedObj);

        auto attackerComponent = getComponent<AttackerComponent>(game,
                                                                 attackerObj);

        healthyComponent.damage(damage);
    }

    void heal(wzc::Event* ev) {
        HealEvent* e = dynamic_cast<HealEvent*>(ev);
        wzc::GameState* game = e->game;
        wzc::GameObject& healedObj = e->healedObj.get();

        HealthyComponent& healthyComponent = getComponent<HealthyComponent>(game,
                                                                            healedObj);
        HealableComponent& healableComponent = getComponent<HealableComponent>(game,
                                                                               healedObj);
        OwnedComponent& ownedComponent = getComponent<OwnedComponent>(game,
                                                                      healedObj);

        InventoryComponent& inventoryComponent = getComponent<InventoryComponent>(game,
            ownedComponent.getOwner().get());

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
    void fin(wzc::Event* ev) {
        wzc::EndEvent* e = dynamic_cast<wzc::EndEvent*>(ev);

        wzc::GameState* game = e->game;

        // look for objects
        for (const std::string& objId : game->getObjectIds()) {
            wzc::GameObject& object = game->getObject(objId);

            if (object.hasComponent(HealEvent::ID)) {
                
            }
        }
    }

    HealthSystem::HealthSystem()
        : System("scho@health", {
                     {HealEvent::ID, heal, false},
                     {DamageEvent::ID, attack, false}
                 }) {
    }
}
