#include "obstruction_component.h"

namespace ccaker {
    const std::string ObstructionComponent::ID = "ocho@obstruction";

    ObstructionComponent::ObstructionComponent(uint16_t size)
            : size(size) {}
    
    wzc::ObjectComponent* ObstructionComponent::clone() const {
        return new ObstructionComponent(size);
    }
}
