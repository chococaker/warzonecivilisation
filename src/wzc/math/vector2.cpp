#include "vector2.h"
#include <cmath>

namespace wzc::math {
    double Vector2::getDistance(const Vector2& other) const {
        return std::sqrt(std::pow(other.x - x, 2) + std::pow(other.y - y, 2));
    }
    
    Vector2 Vector2::operator+(const Vector2& other) const {
        return {static_cast<coordinate_t>(x + other.x), static_cast<coordinate_t>(y+ other.y)};
    }
    
    void Vector2::operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
    }
    
    Vector2 Vector2::operator-(const Vector2& other) const {
        return {static_cast<coordinate_t>(x - other.x), static_cast<coordinate_t>(y - other.y)};
    }
    
    void Vector2::operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
    }
    
    bool Vector2::operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }
    
    size_t Vector2Hash::operator()(const Vector2& vec) const noexcept {
        return std::hash<double>()(vec.x) ^ std::hash<double>()(vec.y);
    }
}
