#pragma once

#include "wzc/math/point2d.h"
#include "wzc/ecs/component/entity/object_component.h"

#include <memory>
#include <stdexcept>
#include <vector>

namespace wzc {
    struct GameObject {
        GameObject(const std::string& id, const math::Point2D& location);
        GameObject(const GameObject& other);
        
        [[nodiscard]] const math::Point2D& getLocation() const;
        void setLocation(const math::Point2D& location);
        
        const std::string& getId() const;

        const std::vector<ObjectComponent*>& getComponents() const;

        ObjectComponent& getComponent(const NamespacedKey& componentTypeKey) const;

        template<typename T>
        T& getComponent(const NamespacedKey& componentTypeKey);

        // attaches a component to the object. overrides previous component if it exists
        void attachComponent(const ObjectComponent& component);

        void removeComponent(const NamespacedKey& componentTypeKey);

        bool hasComponent(const NamespacedKey& componentTypeKey) const;

        bool markedForDestruction = false;

    private:
        std::string id;
        math::Point2D location;
        std::vector<ObjectComponent*> components;
    };

    template<typename T>
    T& GameObject::getComponent(const NamespacedKey& componentTypeKey) {
        ObjectComponent& component = getComponent(componentTypeKey);

        try {
            T& t = dynamic_cast<T&>(component);
            return t;
        } catch (const std::bad_cast&) {
            throw std::invalid_argument("Object component " + to_string(componentTypeKey) + " is not of the requested template type");
        }
    }
}
