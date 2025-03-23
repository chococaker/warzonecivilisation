#include "research_component.h"
#include "chococaker/name_space.h"
#include <stdexcept>

namespace ccaker {
    const wzc::NamespacedKey ResearchComponent::ID(NAMESPACE, "research_component");

    void ResearchComponent::progressTier() {
        if (tier == maxTier) {
            throw std::runtime_error("Tier cannot exceed max tier");
        }
        
        tier++;
    }
    
    ResearchComponent::ResearchComponent(const std::vector<double>& productionModifier, uint16_t maxTier)
            : ResearchComponent(productionModifier, 0, maxTier) {}
    
    ResearchComponent::ResearchComponent(std::vector<double> productionModifier, uint16_t tier, uint16_t maxTier)
            : productionModifier(std::move(productionModifier)), tier(tier), maxTier(maxTier) {
        if (tier > maxTier)
            throw std::runtime_error("Tier cannot exceed max tier");
    }
    
    wzc::PlayerComponent* ResearchComponent::clone() const {
        return new ResearchComponent(productionModifier, tier, maxTier);
    }
}
