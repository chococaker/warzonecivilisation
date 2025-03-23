#pragma once

#include <cstdint>
#include <string>
#include "chococaker/defs/inventory_def.h"
#include "wzc/ecs/component/player/player_component.h"

namespace ccaker {
    struct InventoryComponent final : wzc::PlayerComponent {
        explicit InventoryComponent(Inventory inventory = Inventory());

        static const wzc::NamespacedKey ID;

        const wzc::NamespacedKey& getTypeKey() const override {
            return ID;
        }

        void addMaterial(const std::string& material, uint32_t amount);

        void setMaterial(const std::string& material, uint32_t amount);

        void reduceMaterial(const std::string& material, uint32_t amount);

        void clearMaterial(const std::string& material);

        void clearMaterials();

        bool containsMaterials(const Inventory& materials) const;

        uint32_t getMaterial(const std::string& material) const;

        const Inventory& getAllMaterials() const;

        PlayerComponent *clone() const override;

    private:
        Inventory inventory;
    };
}
