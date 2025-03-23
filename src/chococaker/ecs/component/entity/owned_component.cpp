#include "owned_component.h"

#include "chococaker/name_space.h"
#include "wzc/game_player.h"

namespace ccaker {
    const wzc::NamespacedKey OwnedComponent::ID(NAMESPACE, "owned_component");

    OwnedComponent::OwnedComponent(const wzc::PlayerHandle& owner)
            : owner(owner) { }

    wzc::ObjectComponent* OwnedComponent::clone() const {
        return new OwnedComponent(owner);
    }

    void OwnedComponent::setOwner(const wzc::PlayerHandle& player) {
        this->owner = player;
    }

    const wzc::PlayerHandle& OwnedComponent::getOwner() const {
        return owner;
    }
}
