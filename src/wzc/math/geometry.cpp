#include <stdexcept>
#include <functional>
#include <algorithm>
#include <cmath>
#include "vmath.hpp/vmath_vec.hpp"
#include "vmath.hpp/vmath_vec_fun.hpp"
#include "geometry.h"

using std::max;
using std::min;
using std::sqrt;
using std::pow;

namespace wzc::math {
    typedef vmath_hpp::dvec2 vec2;

    vec2 toVmathVec(const Point2D& point);

    LineSegment::LineSegment(const Point2D& c1, const Point2D& c2) : c1(c1), c2(c2) {
        if (c1 == c2) throw std::invalid_argument("Coordinates may not be the same");
    }

    const Point2D& LineSegment::getC1() const {
        return c1;
    }

    const Point2D& LineSegment::getC2() const {
        return c2;
    }

    double LineSegment::getSlope() const {
        const double run = c1.x - c2.x;
        return run == 0 ? std::numeric_limits<double>::quiet_NaN() : (c1.y - c2.y) / run;
    }

    bool LineSegment::operator==(const LineSegment& other) const {
        return (c1 == other.c1 && c2 == other.c2) || (c1 == other.c2 && c2 == other.c1);
    }

    coordinate_t LineSegment::getYIntercept() const {
        return static_cast<coordinate_t>(std::round(c1.y - (getSlope() * c1.x)));
    }

    double LineSegment::getLength() const {
        return c1.getDistance(c2);
    }

    namespace {
        int getOrientation(const vec2& p, const vec2& q, const vec2& r) {
            const coordinate_t val = (q.y - p.y) * (r.x - q.x) -
                                     (q.x - p.x) * (r.y - q.y);

            if (val == 0) return 0; // collinear

            return val > 0 ? 1 : 2; // clockwise or counterclockwise
        }

        bool isOnSegment(const vec2& p, const vec2& q, const vec2& r) {
            return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x)
                   && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);
        }
    }

    bool LineSegment::intersects(const LineSegment& other) const {
        if (getSlope() == other.getSlope()) return false;

        vec2 p1 = toVmathVec(c1);
        vec2 p2 = toVmathVec(c2);

        // logic to see if they intersect
        vec2 q1 = toVmathVec(other.c1);
        vec2 q2 = toVmathVec(other.c2);

        // if they are the same line, they intersect (only possible if c1 = oth.c2 & c2 = oth.c1)
        if (*this == other)
            return true;

        // check if they are connected - if so, skip
        if (p1 == q1 || p2 == q1 || p1 == q2 || p2 == q2) return false;

        // intersection check
        // https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect

        int o1 = getOrientation(p1, p2, q1);
        int o2 = getOrientation(p1, p2, q2);
        int o3 = getOrientation(q1, q2, p1);
        int o4 = getOrientation(q1, q2, p2);

        if (o1 != o2 && o3 != o4) return false;
        if (o1 == 0 && isOnSegment(p1, q1, p2)) return false;
        if (o2 == 0 && isOnSegment(p1, q2, p2)) return false;
        if (o3 == 0 && isOnSegment(q1, p1, q2)) return false;
        if (o4 == 0 && isOnSegment(q1, p2, q2)) return false;

        return true;
    }

    inline double perpVecDistance(const vec2& c1, const vec2& c2, const vec2& point) {
        // https://paulbourke.net/geometry/pointlineplane/
        const double mag = distance(c1, c2);
        const double u = ((point.x - c1.x) * (c2.x - c1.x) + (point.y - c1.y) * (c2.y - c1.y)) / std::pow(mag, 2);
        const vec2 intersectionPoint = {c1.x + u*(c1.x - c2.x), c1.y + u*(c1.y - c2.y)};
        return distance(intersectionPoint, point);
    }

    double LineSegment::perpDistance(const Point2D& point) const {
        return perpVecDistance(toVmathVec(c1), toVmathVec(c2), toVmathVec(point));
    }

    double LineSegment::perpDistance(const LineSegment& other) const {
        if (intersects(other)) return 0;

        const vec2 p1 = toVmathVec(c1);
        const vec2 q1 = toVmathVec(c2);
        const vec2 p2 = toVmathVec(other.c1);
        const vec2 q2 = toVmathVec(other.c2);

        return std::min({
            perpVecDistance(p1, q1, p2),
            perpVecDistance(p1, q1, q2),
            perpVecDistance(p2, q2, p2),
            perpVecDistance(p2, q2, q2)
        });
    }

    size_t LineSegmentHash::operator()(const LineSegment& line) const {
        std::hash<int16_t> hasher;

        std::size_t hash = hasher(line.getC1().x);
        hash ^= hasher(line.getC1().y) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        hash ^= hasher(line.getC2().x) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        hash ^= hasher(line.getC2().y) + 0x9e3779b9 + (hash << 6) + (hash >> 2);

        return hash;
    }

    Polygon::Polygon(const std::unordered_set<LineSegment, LineSegmentHash>& lines) {
        if (lines.size() < 3) throw std::invalid_argument("Not enough lines to form an enclosed figure");

        // check connectivity
        // not included in map   -> first time seeing the endpoint, add to map
        // included in map:false -> second time seeing the endpoint (at least one segment is
        //                          connected to another segment), change to true
        // included in map:true  -> third time seeing the endpoint (three segments have the same
        //                          vertex), throw exception
        std::unordered_map<Point2D, bool, Point2DHash> connectivityMap;
        for (const LineSegment& line: lines) {
            const Point2D& c1 = line.getC1();

            if (!connectivityMap.count(c1)) {
                connectivityMap[c1] = false;
            } else if (!connectivityMap[line.getC1()]) {
                connectivityMap[c1] = true;
            } else {
                throw std::invalid_argument("Too many vertexes at " + to_string(c1));
            }

            const Point2D& c2 = line.getC2();
            if (!connectivityMap.count(c2)) {
                connectivityMap[c2] = false;
            } else if (!connectivityMap[line.getC1()]) {
                connectivityMap[c2] = true;
            } else {
                throw std::invalid_argument("Too many vertexes at " + to_string(c1));
            }
        }

        for (const std::pair<const Point2D, bool>& pair: connectivityMap) {
            if (!pair.second)
                throw std::invalid_argument(to_string(pair.first) + " is only connected to one line segment");
        }

        // LineSegment segment intersection check
        std::unordered_set intersectionCheckSet(lines);
        while (!intersectionCheckSet.empty()) {
            LineSegment line1 = *intersectionCheckSet.begin();
            intersectionCheckSet.erase(intersectionCheckSet.begin());

            for (const LineSegment& line2: intersectionCheckSet) {
                const Point2D& p1 = line1.getC1();
                const Point2D& q1 = line1.getC2();
                const Point2D& p2 = line2.getC1();
                const Point2D& q2 = line2.getC2();

                if (line1 == line2)
                    throw std::invalid_argument("Duplicate lines of vertexes " + to_string(p1) + ", " + to_string(p2));

                // check if they are connected - if so, skip
                if (p1 == p2 || q1 == p2 || p1 == q2 || q1 == q2) continue;

                if (line1.intersects(line2))
                    throw std::invalid_argument("Lines "
                                                + to_string(p1) + to_string(q1)
                                                + " and "
                                                + to_string(p2) + to_string(q2)
                                                + "intersect each other");
            }
        }
    }

    size_t PolygonHash::operator()(const Polygon& polygon) const noexcept {
        size_t hashValue = 0;
        for (const LineSegment& element: polygon.getLines()) {
            hashValue ^= LineSegmentHash()(element);
        }
        return hashValue;
    }

    const std::unordered_set<LineSegment, LineSegmentHash>& Polygon::getLines() const {
        return lines;
    }

    vmath_hpp::dvec2 toVmathVec(const Point2D& point) {
        return {static_cast<double>(point.x), static_cast<double>(point.y)};
    }
}
