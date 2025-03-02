#ifndef WARZONECIVILISATION_GAME_OBJECT_H
#define WARZONECIVILISATION_GAME_OBJECT_H

#include "wzc/math/vector2.h"

namespace wzc {
    struct GameObject {
        GameObject(const std::string& id, const math::Vector2& location);
        GameObject(const GameObject& other) = default;
        
        [[nodiscard]] const math::Vector2& getLocation() const;
        
        const std::string& getId() const;
    private:
        const std::string id;
        math::Vector2 location;
    };
}

#endif //WARZONECIVILISATION_GAME_OBJECT_H
