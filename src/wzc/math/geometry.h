#ifndef WARZONECIVILISATION_GEOMETRY_H
#define WARZONECIVILISATION_GEOMETRY_H

#include <unordered_set>
#include "wzc/math/vector2.h"

namespace wzc::math {
    struct LineSegment {
        LineSegment(const Vector2& c1, const Vector2& c2);
        LineSegment(const LineSegment& other) = default;
        
        const Vector2& getC1() const;
        const Vector2& getC2() const;
        double getSlope() const;
        coordinate_t getYIntercept() const;
        double getLength() const;
        bool intersects(const LineSegment& other) const;
        
        bool operator==(const LineSegment& other) const;
    private:
        const Vector2 c1;
        const Vector2 c2;
    };
    
    struct LineSegmentHash {
        size_t operator()(const LineSegment& line) const;
    };
    
    struct Polygon {
        explicit Polygon(const std::unordered_set<LineSegment, LineSegmentHash>& lines);
        const std::unordered_set<LineSegment, LineSegmentHash>& getLines() const;
    private:
        const std::unordered_set<LineSegment, LineSegmentHash> lines;
    };
    
    struct PolygonHash {
        size_t operator()(const Polygon& polygon) const noexcept;
    };
}


#endif //WARZONECIVILISATION_GEOMETRY_H
