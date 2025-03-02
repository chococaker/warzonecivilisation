#ifndef WARZONECIVILISATION_SOULBOUND_COMPONENT_H
#define WARZONECIVILISATION_SOULBOUND_COMPONENT_H

#include "wzc/ecs/component/entity/object_component.h"

// If all phylactery components of a player are destroyed, the player dies
namespace ccaker {
    struct PhylacteryComponent final :  wzc::ObjectComponent {
        [[nodiscard]] ObjectComponent* clone() const override;
        
        static const std::string ID;
        
        const std::string& getTypeId() const override {
            return ID;
        }
    };
}


#endif //WARZONECIVILISATION_SOULBOUND_COMPONENT_H
