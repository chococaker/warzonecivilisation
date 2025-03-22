#include "point2d.h"
#include <cmath>

namespace wzc::math {
    double Point2D::getDistance(const Point2D& other) const {
        return std::sqrt(std::pow(other.x - x, 2) + std::pow(other.y - y, 2));
    }
    
    Point2D Point2D::operator+(const Point2D& other) const {
        return {static_cast<coordinate_t>(x + other.x), static_cast<coordinate_t>(y+ other.y)};
    }
    
    void Point2D::operator+=(const Point2D& other) {
        x += other.x;
        y += other.y;
    }
    
    Point2D Point2D::operator-(const Point2D& other) const {
        return {static_cast<coordinate_t>(x - other.x), static_cast<coordinate_t>(y - other.y)};
    }
    
    void Point2D::operator-=(const Point2D& other) {
        x -= other.x;
        y -= other.y;
    }
    
    bool Point2D::operator==(const Point2D& other) const {
        return x == other.x && y == other.y;
    }
    
    size_t Point2DHash::operator()(const Point2D& vec) const noexcept {
        return std::hash<double>()(vec.x) ^ std::hash<double>()(vec.y);
    }
}
