#pragma once

#include <string>

namespace wzc {
    struct NamespacedKey {
        NamespacedKey(const NamespacedKey& other) = default;

        NamespacedKey(std::string name_space, std::string key) : name_space(std::move(name_space)), key(std::move(key)) {}

        const std::string name_space;
        const std::string key;

        bool operator==(const NamespacedKey& other) const {
            return name_space == other.name_space && key == other.key;
        }
    };

    struct NamespacedKeyHash {
        size_t operator()(const NamespacedKey& key) const {
            return std::hash<std::string>()(key.name_space) ^ std::hash<std::string>()(key.key);
        }
    };

    inline std::string to_string(const NamespacedKey& key) {
        return key.name_space + ":" + key.key;
    }
}
