#include "move_event.h"
#include "chococaker/name_space.h"

namespace ccaker {
    const wzc::NamespacedKey MoveEvent::ID(NAMESPACE, "move_system");

    MoveEvent::MoveEvent(const wzc::ObjectHandle& movedObj,
                         const wzc::math::Point2D& to)
            : movedObj(movedObj), to(to) { }
}
