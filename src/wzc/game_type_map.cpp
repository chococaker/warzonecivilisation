#include "game_type_map.h"
#include <stdexcept>

namespace wzc {
    TileTypeMap::TileTypeMap(const math::coordinate_t width, const math::coordinate_t height) : width(width), height(height) {
        if (width <= 0)
            throw std::invalid_argument("width " + std::to_string(width) + " out of bounds");
        if (height <= 0)
            throw std::invalid_argument("height " + std::to_string(height) + " out of bounds");
    }
    
    uint8_t TileTypeMap::getTileType(math::coordinate_t x, math::coordinate_t y) const {
        if (x < 0 || x > width)
            throw std::invalid_argument("x " + std::to_string(x) + " out of bounds");
        if (y < 0 || y > height)
            throw std::invalid_argument("y " + std::to_string(y) + " out of bounds");
        
        return getUncheckedTileType(x, y);
    }
}
