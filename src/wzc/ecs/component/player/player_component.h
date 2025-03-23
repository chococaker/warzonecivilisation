#pragma once

#include <wzc/namespaced_key.h>

namespace wzc {
    struct PlayerComponent {
        [[nodiscard]] virtual PlayerComponent* clone() const = 0;
        virtual void deleteBase() const {}
        virtual ~PlayerComponent() = default;

        virtual const NamespacedKey& getTypeKey() const = 0;
    };
}
