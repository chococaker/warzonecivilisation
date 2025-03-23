#pragma once

#include <wzc/namespaced_key.h>

namespace wzc {
    struct ObjectComponent {
        [[nodiscard]] virtual ObjectComponent* clone() const = 0;
        virtual ~ObjectComponent() = default;
        
        /**
         * Check id_wisdom.txt for more information.
         */
        virtual const NamespacedKey& getTypeKey() const = 0;
    };
}
