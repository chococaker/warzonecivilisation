#include "move_system.h"

#include "wzc/ecs/system/event/end_event.h"
#include "wzc/math/geometry.h"
#include "chococaker/ecs/system/event/move_event.h"
#include "chococaker/ecs/system/event/generic_errors.h"
#include "wzc/game_state.h"
#include "chococaker/ecs/component/entity/movable_component.h"
#include "chococaker/ecs/component/entity/linearobstruction_component.h"
#include "chococaker/util/event_error_util.h"

#include <cmath>

namespace ccaker {
    const std::string MoveSystem::ID = "scho@move";

    void move(wzc::Event* ev, wzc::GameState* game) {
        auto* e = dynamic_cast<MoveEvent*>(ev);

        const wzc::math::Point2D& to = e->to;

        wzc::GameObject& movedObj = e->movedObj.get();

        MovableComponent& movableComponent = getComponent<MovableComponent>(movedObj);

        double distance = movedObj.getLocation().getDistance(to);
        if (movableComponent.exceedsLimit(distance)) {
            throw ResourceLimitExceededError(movedObj.getId(), movableComponent.getAmountLeft(), distance);
        }

        // detecting linear obstructions
        wzc::math::LineSegment moveSegment(movedObj.getLocation(), to);
        for (wzc::GameObject* object : game->getObjectsWith(LinearObstructionComponent::ID)) {
            LinearObstructionComponent& obstructionComponent = getComponent<LinearObstructionComponent>(*object);
            wzc::math::LineSegment wall(object->getLocation(), obstructionComponent.endpoint);
            if (wall.perpDistance(moveSegment) < obstructionComponent.width) {
                throw EnteredBadZoneError(movedObj.getId(), to);
            }
        }

        movableComponent.addAmountMoved(distance);
        movedObj.setLocation(to);
    }

    MoveSystem::MoveSystem()
        : System(ID, {
                     {MoveEvent::ID, move, false}
                 }) {
    }
}
