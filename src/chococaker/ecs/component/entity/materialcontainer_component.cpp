#include "materialcontainer_component.h"
#include "chococaker/name_space.h"

namespace ccaker {
    const wzc::NamespacedKey MaterialContainerComponent::ID(NAMESPACE, "materialcontainer_component");

    MaterialContainerComponent::MaterialContainerComponent(const Inventory& inventory)
            : inventory(inventory) { }
    
    void MaterialContainerComponent::addMaterial(const std::string& material, uint32_t amount) {
        inventory[material] += amount;
    }
    
    void MaterialContainerComponent::setMaterial(const std::string& material, uint32_t amount) {
        inventory[material] = amount;
    }
    
    void MaterialContainerComponent::reduceMaterial(const std::string& material, uint32_t amount) {
        uint32_t currentAmount = getMaterial(material);
        if (currentAmount) {
            uint32_t newAmount = (amount >= currentAmount ? 0 : currentAmount - amount);
            setMaterial(material, newAmount);
        }
    }
    
    void MaterialContainerComponent::clearMaterial(const std::string& material) {
        inventory.erase(material);
    }
    
    void MaterialContainerComponent::clearMaterials() {
        inventory = Inventory();
    }
    
    bool MaterialContainerComponent::containsMaterials(const Inventory& materials) const {
        for (const auto& material : materials) {
            uint32_t amount = getMaterial(material.first);
            if (amount < material.second) return false;
        }
        
        return true;
    }
    
    uint32_t MaterialContainerComponent::getMaterial(const std::string& material) const {
        return inventory.count(material) ? inventory.at(material) : 0;
    }
    
    const Inventory& MaterialContainerComponent::getAllMaterials() const {
        return inventory;
    }
    
    wzc::ObjectComponent* MaterialContainerComponent::clone() const {
        return new MaterialContainerComponent(inventory);
    }
}
