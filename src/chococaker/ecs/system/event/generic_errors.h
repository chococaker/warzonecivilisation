#ifndef WARZONECIVILISATION_GENERIC_ERRORS_H
#define WARZONECIVILISATION_GENERIC_ERRORS_H

#include <string>
#include "wzc/ecs/system/event/event.h"

namespace wzc {
    struct GamePlayer;
    struct GameObject;
}

namespace ccaker {
    struct ComponentNeededError final : wzc::EventError {
        ComponentNeededError(const std::string& ownerId, bool isPlayer, const std::string& componentId);
        
        const std::string& getTypeId() const override {
            return ID;
        }
        
        bool isPlayer() const;
        bool isObject() const;
        
        const std::string ownerId;
        const std::string componentId;
        
        static const std::string ID;
        
    private:
        bool player; // whether the component was held by a player or an object
    };
    
    struct TooExpensiveError final : wzc::EventError {
        TooExpensiveError(const std::string& material, uint32_t amountHad, uint32_t amountNeeded);
        
        const std::string& getTypeId() const override {
            return ID;
        }
        
        const std::string material;
        uint32_t amountHad;
        uint32_t amountNeeded;
        
        static const std::string ID;
    };
    
    struct InvalidPlayerError final : wzc::EventError {
        InvalidPlayerError(const std::string& playerId, const std::string& where);
        
        const std::string& getTypeId() const override {
            return ID;
        }
        
        const std::string playerId;
        const std::string where;
        
        static const std::string ID;
    };
    
    struct InvalidObjectError final : wzc::EventError {
        InvalidObjectError(const std::string& objId, const std::string& where);
        
        const std::string& getTypeId() const override {
            return ID;
        }
        
        const std::string objId;
        const std::string where;
        
        static const std::string ID;
    };
}

#endif
