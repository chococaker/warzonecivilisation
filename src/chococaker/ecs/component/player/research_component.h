#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include "wzc/ecs/component/player/player_component.h"

namespace ccaker {
    struct ResearchComponent final : wzc::PlayerComponent {
        ResearchComponent(const std::vector<double>& productionModifier, uint16_t tier);
        
        ResearchComponent(std::vector<double> productionModifier, uint16_t tier, uint16_t maxTier);
        
        void progressTier();
        
        static const std::string ID;
        
        const std::string& getTypeId() const override {
            return ID;
        }
        
        PlayerComponent* clone() const override;
    
    private:
        std::vector<double> productionModifier;
        uint16_t tier;
        uint16_t maxTier;
    };
}
