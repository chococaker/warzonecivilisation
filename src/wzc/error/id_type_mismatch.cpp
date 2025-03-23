#include "id_type_mismatch.h"

namespace wzc {
    IdTypeMismatch::IdTypeMismatch(const NamespacedKey& typeId, const std::type_info& typeInfo)
            : std::runtime_error(to_string(typeId) + " does not match requested type " + typeInfo.name()),
              typeId(typeId),
              typeInfo(typeInfo) {}
}
