#ifndef WARZONECIVILISATION_VECTOR2_H
#define WARZONECIVILISATION_VECTOR2_H

#include <cstdint>
#include <string>

namespace wzc::math {
    typedef int16_t coordinate_t;
    
    struct Vector2 {
        Vector2(const coordinate_t x, const coordinate_t y) : x(x), y(y) {}
        Vector2(const Vector2& other) = default;
        
        coordinate_t x;
        coordinate_t y;
        
        [[nodiscard]] double getDistance(const Vector2& other) const;
        
        Vector2 operator+(const Vector2& other) const;
        void operator+=(const Vector2& other);
        Vector2 operator-(const Vector2& other) const;
        void operator-=(const Vector2& other);
        bool operator==(const Vector2& other) const;
    };
    
    struct Vector2Hash {
        size_t operator()(const Vector2& vec) const noexcept;
    };
    
    inline std::string to_string(const Vector2& val) {
        return "(" + std::to_string(val.x) + "," + std::to_string(val.y) + ")";
    }
}

#endif //WARZONECIVILISATION_VECTOR2_H
