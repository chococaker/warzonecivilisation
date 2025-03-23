#pragma once

#include <stdexcept>
#include <wzc/namespaced_key.h>

namespace wzc {
    struct ComponentNotFound final : std::runtime_error {
        explicit ComponentNotFound(const NamespacedKey& componentTypeKey);

        const NamespacedKey componentTypeId;
    };
}
