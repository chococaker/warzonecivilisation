#include <stdexcept>
#include <functional>
#include <algorithm>
#include <cmath>
#include "geometry.h"

using std::max;
using std::min;
using std::sqrt;
using std::pow;

namespace wzc::math {
    LineSegment::LineSegment(const Vector2 &c1, const Vector2 &c2) : c1(c1), c2(c2) {
        if (c1 == c2) throw std::invalid_argument("Coordinates may not be the same");
    }

    const Vector2 &LineSegment::getC1() const {
        return c1;
    }

    const Vector2 &LineSegment::getC2() const {
        return c2;
    }

    double LineSegment::getSlope() const {
        const double run = c1.x - c2.x;
        return run == 0 ? std::numeric_limits<double>::quiet_NaN() : (c1.y - c2.y) / run;
    }

    bool LineSegment::operator==(const LineSegment &other) const {
        return (c1 == other.c1 && c2 == other.c2) || (c1 == other.c2 && c2 == other.c1);
    }

    coordinate_t LineSegment::getYIntercept() const {
        return static_cast<coordinate_t>(std::round(c1.y - (getSlope() * c1.x)));
    }

    double LineSegment::getLength() const {
        return c1.getDistance(c2);
    }

    namespace {
        int getOrientation(const Vector2 &p, const Vector2 &q, const Vector2 &r) {
            const coordinate_t val = (q.y - p.y) * (r.x - q.x) -
                                     (q.x - p.x) * (r.y - q.y);

            if (val == 0) return 0; // collinear

            return (val > 0) ? 1 : 2; // clockwise or counterclockwise
        }

        bool isOnSegment(const Vector2 &p, const Vector2 &q, const Vector2 &r) {
            return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x)
                   && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);
        }
    }

    bool LineSegment::intersects(const LineSegment &other) const {
        if (getSlope() == other.getSlope()) return false;

        // logic to see if they intersect
        const Vector2 &q1 = other.getC1();
        const Vector2 &q2 = other.getC2();

        // if they are the same line, they intersect (only possible if c1 = oth.c2 & c2 = oth.c1)
        if (*this == other)
            return true;

        // check if they are connected - if so, skip
        if (c1 == q1 || c2 == q1 || c1 == q2 || c2 == q2) return false;

        // intersection check
        // https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect
        int o1 = getOrientation(c1, c2, q1);
        int o2 = getOrientation(c1, c2, q2);
        int o3 = getOrientation(q1, q2, c1);
        int o4 = getOrientation(q1, q2, c2);

        if (o1 != o2 && o3 != o4) return false;
        if (o1 == 0 && isOnSegment(c1, q1, c2)) return false;
        if (o2 == 0 && isOnSegment(c1, q2, c2)) return false;
        if (o3 == 0 && isOnSegment(q1, c1, q2)) return false;
        if (o4 == 0 && isOnSegment(q1, c2, q2)) return false;

        return true;
    }

    size_t LineSegmentHash::operator()(const LineSegment &landiline) const {
        std::hash<int16_t> hasher;

        std::size_t hash = hasher(landiline.getC1().x);
        hash ^= hasher(landiline.getC1().y) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        hash ^= hasher(landiline.getC2().x) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        hash ^= hasher(landiline.getC2().y) + 0x9e3779b9 + (hash << 6) + (hash >> 2);

        return hash;
    }

    Polygon::Polygon(const std::unordered_set<LineSegment, LineSegmentHash> &lines) {
        if (lines.size() < 3) throw std::invalid_argument("Not enough lines to form an enclosed figure");

        // check connectivity
        // not included in map   -> first time seeing the endpoint, add to map
        // included in map:false -> second time seeing the endpoint (at least one segment is
        //                          connected to another segment), change to true
        // included in map:true  -> third time seeing the endpoint (three segments have the same
        //                          vertex), throw exception
        std::unordered_map<Vector2, bool, Vector2Hash> connectivityMap;
        for (const LineSegment &landiline: lines) {
            const Vector2 &c1 = landiline.getC1();

            if (!connectivityMap.count(c1)) {
                connectivityMap[c1] = false;
            } else if (!connectivityMap[landiline.getC1()]) {
                connectivityMap[c1] = true;
            } else {
                throw std::invalid_argument("Too many vertexes at " + to_string(c1));
            }

            const Vector2 &c2 = landiline.getC2();
            if (!connectivityMap.count(c2)) {
                connectivityMap[c2] = false;
            } else if (!connectivityMap[landiline.getC1()]) {
                connectivityMap[c2] = true;
            } else {
                throw std::invalid_argument("Too many vertexes at " + to_string(c1));
            }
        }

        for (const std::pair<const Vector2, bool> &pair: connectivityMap) {
            if (!pair.second)
                throw std::invalid_argument(to_string(pair.first) + " is only connected to one line segment");
        }

        // LineSegment segment intersection check
        std::unordered_set<LineSegment, LineSegmentHash> intersectionCheckSet(lines);
        while (!intersectionCheckSet.empty()) {
            LineSegment landiline1 = *intersectionCheckSet.begin();
            intersectionCheckSet.erase(intersectionCheckSet.begin());

            for (const LineSegment &landiline2: intersectionCheckSet) {
                const Vector2 &p1 = landiline1.getC1();
                const Vector2 &q1 = landiline1.getC2();
                const Vector2 &p2 = landiline2.getC1();
                const Vector2 &q2 = landiline2.getC2();

                if (landiline1 == landiline2)
                    throw std::invalid_argument("Duplicate lines of vertexes " + to_string(p1) + ", " + to_string(p2));

                // check if they are connected - if so, skip
                if (p1 == p2 || q1 == p2 || p1 == q2 || q1 == q2) continue;

                if (landiline1.intersects(landiline2))
                    throw std::invalid_argument("Lines "
                                                + to_string(p1) + to_string(q1)
                                                + " and "
                                                + to_string(p2) + to_string(q2)
                                                + "intersect each other");
            }
        }
    }

    size_t PolygonHash::operator()(const Polygon &polygon) const noexcept {
        size_t hashValue = 0;
        for (const LineSegment &element: polygon.getLines()) {
            hashValue ^= LineSegmentHash()(element);
        }
        return hashValue;
    }

    const std::unordered_set<LineSegment, LineSegmentHash>& Polygon::getLines() const {
        return lines;
    }
}
