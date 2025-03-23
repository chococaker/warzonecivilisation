#include "component_not_found.h"

namespace wzc {
    ComponentNotFound::ComponentNotFound(const NamespacedKey& componentTypeKey)
            : std::runtime_error("Component not found of ID " + to_string(componentTypeKey)),
              componentTypeId(componentTypeKey) {}
}
