#include "phylactery_component.h"
#include "chococaker/name_space.h"

namespace ccaker {
    const wzc::NamespacedKey PhylacteryComponent::ID(NAMESPACE, "phylactery_component");

    wzc::ObjectComponent* PhylacteryComponent::clone() const {
        return new PhylacteryComponent();
    }
}
