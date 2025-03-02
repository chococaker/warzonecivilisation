#include "game_object.h"

#include "error/component_not_found.h"

#include <algorithm>
#include <cassert>

namespace wzc {
    GameObject::GameObject(const std::string& id, const math::Vector2& location)
            : id(id), location(location) { }

    GameObject::GameObject(const GameObject& other)
        : id(other.id), location(other.location) {
        components.reserve(other.components.size());
        for (const auto& component : other.components) {
            components.push_back(component->clone());
        }
    }
    
    const math::Vector2& GameObject::getLocation() const {
        return location;
    }
    
    const std::string& GameObject::getId() const {
        return id;
    }

    const std::vector<ObjectComponent*>& GameObject::getComponents() const {
        return components;
    }

    ObjectComponent& GameObject::getComponent(const std::string& componentTypeId) const {
        for (ObjectComponent* component : components) {
            if (component->getTypeId() == componentTypeId) {
                return *component;
            }
        }

        throw ComponentNotFound(componentTypeId);
    }

    void GameObject::attachComponent(const ObjectComponent& component) {
        // check if component is already in components
        size_t index = 0;
        for (const ObjectComponent* ownedComponent : components) {
            if (ownedComponent->getTypeId() == component.getTypeId()) {}
            index++;
        }

        ObjectComponent* newComponent = component.clone();

        if (index != components.size()) {
            components[index] = newComponent;
        } else {
            components.push_back(newComponent);
        }
    }

    void GameObject::removeComponent(const std::string& componentTypeId) {
        components.erase(std::remove_if(components.begin(), components.end(),
            [componentTypeId](const ObjectComponent* component) {
                return component->getTypeId() == componentTypeId;
            }), components.end());
    }

    bool GameObject::hasComponent(const std::string& componentTypeId) const {
        for (const ObjectComponent* component : components) {
            if (component->getTypeId() == componentTypeId) {
                return true;
            }
        }

        return false;
    }
}
