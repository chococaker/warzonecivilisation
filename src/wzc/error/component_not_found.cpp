#include "component_not_found.h"

namespace wzc {
    ComponentNotFound::ComponentNotFound(const std::string& componentTypeId)
            : std::runtime_error("Component not found of ID " + componentTypeId),
              componentTypeId(componentTypeId) {}
}
