#include "null_encounter.h"

namespace wzc {
    NullEncounter::NullEncounter(const std::string& where)
            : std::runtime_error("Unexpected null pointer encountered at " + where) { }
}
