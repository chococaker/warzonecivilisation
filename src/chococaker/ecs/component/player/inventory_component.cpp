#include "inventory_component.h"
#include "chococaker/name_space.h"

#include <algorithm>
#include <utility>

namespace ccaker {
    const wzc::NamespacedKey InventoryComponent::ID(NAMESPACE, "inventory_component");
    
    InventoryComponent::InventoryComponent(Inventory inventory)
            : inventory(std::move(inventory)) { }
    
    void InventoryComponent::addMaterial(const std::string& material, uint32_t amount) {
        inventory[material] += amount;
    }
    
    void InventoryComponent::setMaterial(const std::string& material, uint32_t amount) {
        inventory[material] = amount;
    }
    
    void InventoryComponent::reduceMaterial(const std::string& material, uint32_t amount) {
        if (const uint32_t currentAmount = getMaterial(material)) {
            const uint32_t newAmount = (amount >= currentAmount ? 0 : currentAmount - amount);
            setMaterial(material, newAmount);
        }
    }
    
    void InventoryComponent::clearMaterial(const std::string& material) {
        inventory.erase(material);
    }
    
    void InventoryComponent::clearMaterials() {
        inventory = Inventory();
    }
    
    bool InventoryComponent::containsMaterials(const Inventory& materials) const {
        for (const auto& [materialId, amount] : materials) {
            if (const uint32_t thisAmount = getMaterial(materialId); amount < thisAmount) {
                return false;
            }
        }

        return true;
    }
    
    uint32_t InventoryComponent::getMaterial(const std::string& material) const {
        return inventory.count(material) ? inventory.at(material) : 0;
    }
    
    const Inventory& InventoryComponent::getAllMaterials() const {
        return inventory;
    }
    
    wzc::PlayerComponent* InventoryComponent::clone() const {
        return new InventoryComponent(inventory);
    }
}
