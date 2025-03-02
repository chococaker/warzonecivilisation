#ifndef WZC_COMPONENT_NOT_FOUND_H
#define WZC_COMPONENT_NOT_FOUND_H

#include <stdexcept>

namespace wzc {
    struct ComponentNotFound final : std::runtime_error {
        explicit ComponentNotFound(const std::string& componentTypeId);

        const std::string componentTypeId;
    };
}

#endif // WZC_COMPONENT_NOT_FOUND_H
