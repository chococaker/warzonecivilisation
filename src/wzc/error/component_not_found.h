#pragma once

#include <stdexcept>

namespace wzc {
    struct ComponentNotFound final : std::runtime_error {
        explicit ComponentNotFound(const std::string& componentTypeId);

        const std::string componentTypeId;
    };
}
