#ifndef WARZONECIVILISATION_GAME_OBJECT_H
#define WARZONECIVILISATION_GAME_OBJECT_H

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

        ObjectComponent& getComponent(const std::string& componentTypeId) const;

        template<typename T>
        T& getComponent(const std::string& componentTypeId);

        // attaches a component to the object. overrides previous component if it exists
        void attachComponent(const ObjectComponent& component);

        void removeComponent(const std::string& componentTypeId);

        bool hasComponent(const std::string& componentTypeId) const;

        bool markedForDestruction = false;

    private:
        std::string id;
        math::Point2D location;
        std::vector<ObjectComponent*> components;
    };

    template<typename T>
    T& GameObject::getComponent(const std::string& componentTypeId) {
        ObjectComponent& component = getComponent(componentTypeId);

        try {
            T& t = dynamic_cast<T&>(component);
            return t;
        } catch (const std::bad_cast&) {
            throw std::invalid_argument("Object component " + componentTypeId + " is not of the requested template type");
        }
    }
}

#endif //WARZONECIVILISATION_GAME_OBJECT_H
