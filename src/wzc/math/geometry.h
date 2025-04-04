#pragma once

#include <unordered_set>
#include "wzc/math/point2d.h"

namespace wzc::math {
    struct LineSegment {
        LineSegment(const Point2D& c1, const Point2D& c2);
        LineSegment(const LineSegment& other) = default;
        
        const Point2D& getC1() const;
        const Point2D& getC2() const;
        double getSlope() const;
        coordinate_t getYIntercept() const;
        double getLength() const;
        bool intersects(const LineSegment& other) const;

        double perpDistance(const Point2D& point) const;
        double perpDistance(const LineSegment& other) const;

        bool operator==(const LineSegment& other) const;
    private:
        const Point2D c1;
        const Point2D c2;
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
