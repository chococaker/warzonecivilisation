#pragma once

#include <cstdint>
#include <string>
#include "wzc/ecs/system/event/event.h"
#include "wzc/math/point2d.h"

namespace wzc {
    struct GamePlayer;
    struct GameObject;
}

namespace ccaker {
    struct ComponentNeededError final : wzc::EventError {
        ComponentNeededError(const std::string& ownerId, const wzc::NamespacedKey& componentId);
        
        const wzc::NamespacedKey& getTypeKey() const override {
            return ID;
        }
        
        const std::string ownerId;
        const wzc::NamespacedKey componentId;
        
        static const wzc::NamespacedKey ID;
    };
    
    struct TooExpensiveError final : wzc::EventError {
        TooExpensiveError(const std::string& material, uint32_t amountHad, uint32_t amountNeeded);
        
        const wzc::NamespacedKey& getTypeKey() const override {
            return ID;
        }
        
        const std::string material;
        uint32_t amountHad;
        uint32_t amountNeeded;
        
        static const wzc::NamespacedKey ID;
    };
    
    struct InvalidPlayerError final : wzc::EventError {
        InvalidPlayerError(const std::string& playerId, const std::string& where);
        
        const wzc::NamespacedKey& getTypeKey() const override {
            return ID;
        }
        
        const std::string playerId;
        const std::string where;
        
        static const wzc::NamespacedKey ID;
    };
    
    struct InvalidObjectError final : wzc::EventError {
        InvalidObjectError(const std::string& objId, const std::string& where);
        
        const wzc::NamespacedKey& getTypeKey() const override {
            return ID;
        }
        
        const std::string objId;
        const std::string where;
        
        static const wzc::NamespacedKey ID;
    };

    struct OutOfRangeError final : wzc::EventError {
        OutOfRangeError(const std::string& objId, double allowedRange, double attemptedRange);

        const wzc::NamespacedKey& getTypeKey() const override {
            return ID;
        }

        const std::string objId;
        double allowedRange;
        double attemptedRange;

        static const wzc::NamespacedKey ID;
    };

    struct ResourceLimitExceededError final : wzc::EventError {
        ResourceLimitExceededError(const std::string& objId, double allowedRange, double attemptedRange);

        const wzc::NamespacedKey& getTypeKey() const override {
            return ID;
        }

        const std::string objId;
        double allowedRange;
        double attemptedRange;

        static const wzc::NamespacedKey ID;
    };

    struct EnteredBadZoneError final : wzc::EventError {
        EnteredBadZoneError(const std::string& objId, const wzc::math::Point2D& to);

        const wzc::NamespacedKey& getTypeKey() const override {
            return ID;
        }

        const std::string objId;
        const wzc::math::Point2D to;

        static const wzc::NamespacedKey ID;
    };
}
