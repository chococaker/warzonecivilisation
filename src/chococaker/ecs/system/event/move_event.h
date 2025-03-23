#pragma once

#include "wzc/math/point2d.h"
#include "wzc/ecs/system/event/event.h"
#include "wzc/handle/object_handle.h"

namespace ccaker {
    struct MoveEvent final : wzc::Event {
        MoveEvent(const wzc::ObjectHandle& movedObj,
                  const wzc::math::Point2D& to);

        const std::string& getTypeId() const override {
            return ID;
        }

        static const std::string ID;

        const wzc::ObjectHandle& movedObj;
        const wzc::math::Point2D to;
    };
}
