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

        if (healthyComponent.isDead()) {
            game
        }

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

        for (const auto& entry: healableComponent.fullHealCost) {
            uint32_t cost = static_cast<uint32_t>(std::ceil(entry.second * healPercent));

            uint32_t amountHad = inventoryComponent.getMaterial(entry.first);

            if (amountHad < cost)
                throw TooExpensiveError(entry.first, amountHad, cost);

            inventoryComponent.reduceMaterial(entry.first, cost);
        }

        healthyComponent.heal(e->amountHeal);
    }

    HealthSystem::HealthSystem()
        : System("scho@health", {
                     {HealEvent::ID, heal},
                     {DamageEvent::ID, attack}
                 }) {
    }
}
