#pragma once

#include <stdexcept>

namespace wzc {
    struct NullEncounter final : std::runtime_error {
        explicit NullEncounter(const std::string& where);
        
        const std::string where;
    };

    inline void nullCheck(const void* o, const std::string& where) {
        if (o == nullptr) {
            throw NullEncounter(where);
        }
    }
}
