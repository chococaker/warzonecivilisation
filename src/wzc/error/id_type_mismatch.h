#pragma once

#include <stdexcept>
#include <typeinfo>
#include <wzc/namespaced_key.h>

namespace wzc {
    struct IdTypeMismatch final : std::runtime_error {
        IdTypeMismatch(const NamespacedKey& typeId, const std::type_info& typeInfo);

        const NamespacedKey typeId;
        const std::type_info& typeInfo;
    };
}
