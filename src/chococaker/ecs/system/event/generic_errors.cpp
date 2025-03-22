#include "generic_errors.h"
#include "wzc/game_player.h"

namespace ccaker {
    const std::string ComponentNeededError::ID = "rcho@component_needed";
    const std::string TooExpensiveError::ID = "rcho@too_expensive";
    const std::string InvalidPlayerError::ID = "rcho@invalid_player";
    const std::string InvalidObjectError::ID = "rcho@invalid_object";
    const std::string OutOfRangeError::ID = "rcho@out_of_range";
    const std::string ResourceLimitExceededError::ID = "rcho@resource_limit_exceeded";
    const std::string EnteredBadZoneError::ID = "rcho@entered_bad_zone";

    ComponentNeededError::ComponentNeededError(const std::string& ownerId,
                                               bool isPlayer,
                                               const std::string& componentId)
        : ownerId(ownerId), componentId(componentId), player(isPlayer) {
    }

    bool ComponentNeededError::isPlayer() const {
        return player;
    }

    bool ComponentNeededError::isObject() const {
        return !player;
    }

    TooExpensiveError::TooExpensiveError(const std::string& material,
                                         uint32_t amountHad,
                                         uint32_t amountNeeded)
        : material(material), amountHad(amountHad), amountNeeded(amountNeeded) {
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
