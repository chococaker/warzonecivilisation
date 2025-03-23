#pragma once

#include <stdexcept>
#include <typeinfo>

namespace wzc {
    struct IdTypeMismatch final : std::runtime_error {
        IdTypeMismatch(const std::string& typeId, const std::type_info& typeInfo);
        
        const std::string typeId;
        const std::type_info& typeInfo;
    };
}
