#include "generic_errors.h"
#include "wzc/game_player.h"
#include "chococaker/name_space.h"

namespace ccaker {
    const wzc::NamespacedKey ComponentNeededError::ID(NAMESPACE, "component_needed_error");
    const wzc::NamespacedKey TooExpensiveError::ID(NAMESPACE, "too_expensive_error");
    const wzc::NamespacedKey InvalidPlayerError::ID(NAMESPACE, "invalid_player_error");
    const wzc::NamespacedKey InvalidObjectError::ID(NAMESPACE, "invalid_object_error");
    const wzc::NamespacedKey OutOfRangeError::ID(NAMESPACE, "out_of_range_error");
    const wzc::NamespacedKey ResourceLimitExceededError::ID(NAMESPACE, "resource_limit_exceeded_error");
    const wzc::NamespacedKey EnteredBadZoneError::ID(NAMESPACE, "entered_bad_zone_error");

    ComponentNeededError::ComponentNeededError(const std::string& ownerId,
                                               const wzc::NamespacedKey& componentId)
        : EventError(ownerId + " requires component " + to_string(componentId)),
          ownerId(ownerId), componentId(componentId) {
    }

    TooExpensiveError::TooExpensiveError(const std::string& material,
                                         uint32_t amountHad,
                                         uint32_t amountNeeded)
        : EventError("Need " + std::to_string(amountNeeded) + " of " + material + ", have " + std::to_string(amountHad)),
          material(material), amountHad(amountHad), amountNeeded(amountNeeded) {
    }

    InvalidPlayerError::InvalidPlayerError(const std::string& playerId, const std::string& where)
        : EventError("Invalid player ID " + playerId + " at " + where),
          playerId(playerId), where(where) {
    }

    InvalidObjectError::InvalidObjectError(const std::string& objId, const std::string& where)
        : EventError("Invalid object ID " + objId + " at " + where),
          objId(objId), where(where) {
    }

    OutOfRangeError::OutOfRangeError(const std::string& objId, double allowedRange, double attemptedRange)
        : EventError(
              "Object ID " + objId + " attempted operation at distance " + std::to_string(allowedRange) +
              ", which is out of range " + std::to_string(attemptedRange)),
          objId(objId), allowedRange(allowedRange), attemptedRange(attemptedRange) {
    }

    ResourceLimitExceededError::ResourceLimitExceededError(const std::string& objId, double allowedRange,
                                                           double attemptedRange)
        : EventError(
              "Object ID " + objId + " attempted operation with resource " + std::to_string(allowedRange) +
              ", which is out of limit " + std::to_string(attemptedRange)),
          objId(objId), allowedRange(allowedRange), attemptedRange(attemptedRange) {
    }

    EnteredBadZoneError::EnteredBadZoneError(const std::string& objId, const wzc::math::Point2D& to)
        : EventError(
              "Object ID " + objId + " attempted to enter " + to_string(to) + ", which intersects with a bad zone"),
          objId(objId), to(to) {
    }
}
