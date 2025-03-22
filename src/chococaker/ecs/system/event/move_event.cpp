#include "move_event.h"

namespace ccaker {
    const std::string MoveEvent::ID = "echo@move";

    MoveEvent::MoveEvent(const wzc::ObjectHandle& movedObj,
                         const wzc::math::Point2D& to)
            : movedObj(movedObj), to(to) { }
}
