#pragma once

#include "wzc/math/point2d.h"

namespace wzc {
    struct TileTypeMap {
        TileTypeMap(math::coordinate_t width, math::coordinate_t height);
        [[nodiscard]] virtual uint8_t getTileType(math::coordinate_t x, math::coordinate_t y) const = 0;
        
        const math::coordinate_t width;
        const math::coordinate_t height;
        
        virtual ~TileTypeMap() = default;
    protected:
        [[nodiscard]] virtual uint8_t getUncheckedTileType(uint16_t x, uint16_t y) const = 0;
    };
}
