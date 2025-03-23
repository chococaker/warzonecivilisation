#pragma once

#include <cstdint>
#include <string>

namespace wzc::math {
    typedef int16_t coordinate_t;
    
    struct Point2D {
        Point2D(const coordinate_t x, const coordinate_t y) : x(x), y(y) {}
        Point2D(const Point2D& other) = default;
        
        coordinate_t x;
        coordinate_t y;
        
        [[nodiscard]] double getDistance(const Point2D& other) const;

        Point2D norm();
        
        Point2D operator+(const Point2D& other) const;
        void operator+=(const Point2D& other);
        Point2D operator-(const Point2D& other) const;
        void operator-=(const Point2D& other);
        bool operator==(const Point2D& other) const;
    };
    
    struct Point2DHash {
        size_t operator()(const Point2D& vec) const noexcept;
    };
    
    inline std::string to_string(const Point2D& val) {
        return "(" + std::to_string(val.x) + "," + std::to_string(val.y) + ")";
    }
}
