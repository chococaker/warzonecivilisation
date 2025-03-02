#include "owned_component.h"
#include "wzc/game_player.h"

namespace ccaker {
    const std::string OwnedComponent::ID = "ocho@owned";
    
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
