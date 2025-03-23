#pragma once

#include "wzc/math/point2d.h"
#include "wzc/ecs/system/event/event.h"
#include "wzc/handle/object_handle.h"

namespace ccaker {
    struct MoveEvent final : wzc::Event {
        MoveEvent(const wzc::ObjectHandle& movedObj,
                  const wzc::math::Point2D& to);

        const wzc::NamespacedKey& getTypeKey() const override {
            return ID;
        }

        static const wzc::NamespacedKey ID;

        const wzc::ObjectHandle& movedObj;
        const wzc::math::Point2D to;
    };
}
