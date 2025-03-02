#include "phylactery_component.h"

namespace ccaker {
    const std::string PhylacteryComponent::ID = "ocho@phylactery";

    wzc::ObjectComponent* PhylacteryComponent::clone() const {
        return new PhylacteryComponent();
    }
}
