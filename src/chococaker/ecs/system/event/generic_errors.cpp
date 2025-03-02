#include "generic_errors.h"
#include "wzc/game_player.h"

#include <stdexcept>

namespace ccaker {
    const std::string ComponentNeededError::ID = "rcho@component_needed";
    const std::string TooExpensiveError::ID = "rcho@too_expensive";
    const std::string InvalidPlayerError::ID = "rcho@invalid_player";
    const std::string InvalidObjectError::ID = "rcho@invalid_object";
    
    ComponentNeededError::ComponentNeededError(const std::string& ownerId,
                                               bool isPlayer,
                                               const std::string& componentId)
            : ownerId(ownerId), player(isPlayer), componentId(componentId) { }
    
    bool ComponentNeededError::isPlayer() const {
        return player;
    }
    
    bool ComponentNeededError::isObject() const {
        return !player;
    }
    
    TooExpensiveError::TooExpensiveError(const std::string& material,
                                         uint32_t amountHad,
                                         uint32_t amountNeeded)
            : material(material), amountHad(amountHad), amountNeeded(amountNeeded) { }
    
    InvalidPlayerError::InvalidPlayerError(const std::string& playerId, const std::string& where)
            : wzc::EventError("Invalid player ID " + playerId + " at " + where),
              playerId(playerId), where(where) {}
    
    InvalidObjectError::InvalidObjectError(const std::string& objId, const std::string& where)
            : wzc::EventError("Invalid object ID " + objId + " at " + where),
              objId(objId), where(where) {}
}
