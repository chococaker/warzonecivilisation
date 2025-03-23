#pragma once

#include <string>
#include "wzc/ecs/component/entity/object_component.h"
#include "wzc/handle/player_handle.h"

namespace ccaker {
    struct OwnedComponent final :  wzc::ObjectComponent {
        explicit OwnedComponent(const wzc::PlayerHandle& owner);
        
        [[nodiscard]] ObjectComponent* clone() const override;

        const wzc::PlayerHandle& getOwner() const;

        void setOwner(const wzc::PlayerHandle& player);

        static const wzc::NamespacedKey ID;
        const wzc::NamespacedKey& getTypeKey() const override {
            return ID;
        }

    private:
        wzc::PlayerHandle owner;
    };
}
