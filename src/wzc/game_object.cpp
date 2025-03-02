#include "game_object.h"
#include "wzc/game_player.h"

namespace wzc {
    GameObject::GameObject(const std::string& id, const math::Vector2& location)
            : id(id), location(location) { }
    
    const math::Vector2& GameObject::getLocation() const {
        return location;
    }
    
    const std::string& GameObject::getId() const {
        return id;
    }
}
