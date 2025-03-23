#pragma once

#include "object_component.h"

namespace wzc {
    // Represents a component for an object that is specifically meant for holding data. Data
    // components should be ignored by any mod that is unrelated to this one. Note that this
    // component does not hold data itself, merely acting as a marker for mods to not touch the
    // owner of the component if it is not related to the mod.
    //
    // An example of a case where a data component may be needed is when a piece of data may be
    // needed to be saved across turns that encompasses the entire game. This may be needed when:
    //   - "States" of the game need to be represented, which affect more than one player or entity
    //   - A global currency is held among all players
    struct DataComponent final :  ObjectComponent {
        DataComponent();
        
        ObjectComponent* clone() const override {
            return new DataComponent();
        }
        
        const std::string& getTypeId() const override {
            return ID;
        }
        
        static const std::string ID;
    };
    
    const std::string DataComponent::ID = "o000@data";
}
