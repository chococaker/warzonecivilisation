#include "game_object.h"

#include "error/component_not_found.h"

#include <algorithm>
#include <cassert>

namespace wzc {
    GameObject::GameObject(const std::string& id, const math::Point2D& location)
            : id(id), location(location) { }

    GameObject::GameObject(const GameObject& other)
        : id(other.id), location(other.location) {
        components.reserve(other.components.size());
        for (const auto& component : other.components) {
            components.push_back(component->clone());
        }
    }
    
    const math::Point2D& GameObject::getLocation() const {
        return location;
    }

    void GameObject::setLocation(const math::Point2D& location) {
        this->location = location;
    }
    
    const std::string& GameObject::getId() const {
        return id;
    }

    const std::vector<ObjectComponent*>& GameObject::getComponents() const {
        return components;
    }

    ObjectComponent& GameObject::getComponent(const NamespacedKey& componentTypeKey) const {
        for (ObjectComponent* component : components) {
            if (component->getTypeKey() == componentTypeKey) {
                return *component;
            }
        }

        throw ComponentNotFound(componentTypeKey);
    }

    void GameObject::attachComponent(const ObjectComponent& component) {
        // check if component is already in components
        size_t index = 0;
        for (const ObjectComponent* ownedComponent : components) {
            if (ownedComponent->getTypeKey() == component.getTypeKey()) {}
            index++;
        }

        ObjectComponent* newComponent = component.clone();

        if (index != components.size()) {
            components[index] = newComponent;
        } else {
            components.push_back(newComponent);
        }
    }

    void GameObject::removeComponent(const NamespacedKey& componentTypeKey) {
        components.erase(std::remove_if(components.begin(), components.end(),
            [componentTypeKey](const ObjectComponent* component) {
                return component->getTypeKey() == componentTypeKey;
            }), components.end());
    }

    bool GameObject::hasComponent(const NamespacedKey& componentTypeKey) const {
        for (const ObjectComponent* component : components) {
            if (component->getTypeKey() == componentTypeKey) {
                return true;
            }
        }

        return false;
    }
}
