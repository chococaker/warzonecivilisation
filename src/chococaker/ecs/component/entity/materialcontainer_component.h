#pragma once

#include "wzc/ecs/component/entity/object_component.h"
#include <unordered_map>
#include <cstdint>
#include "chococaker/defs/inventory_def.h"

namespace ccaker {
struct MaterialContainerComponent : wzc::ObjectComponent {
    explicit MaterialContainerComponent(const Inventory& inventory = Inventory());
        
        static const std::string ID;
        
        const std::string& getTypeId() const override {
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
    
        ObjectComponent* clone() const override;
    private:
        Inventory inventory;
    };
}
