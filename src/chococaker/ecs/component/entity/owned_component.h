#pragma once

#include <string>
#include "wzc/ecs/component/entity/object_component.h"
#include "wzc/handle/player_handle.h"

namespace ccaker {
    struct OwnedComponent final :  wzc::ObjectComponent {
        explicit OwnedComponent(const wzc::PlayerHandle& owner);
        
        [[nodiscard]] ObjectComponent* clone() const override;
        
        static const std::string ID;
        
        const std::string& getTypeId() const override {
            return ID;
        }
        
        const wzc::PlayerHandle& getOwner() const;
        
        void setOwner(const wzc::PlayerHandle& player);
    
    private:
        wzc::PlayerHandle owner;
    };
}
