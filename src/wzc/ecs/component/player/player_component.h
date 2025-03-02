#ifndef WARZONECIVILISATION_PLAYER_COMPONENT_H
#define WARZONECIVILISATION_PLAYER_COMPONENT_H

#include <string>

namespace wzc {
    struct PlayerComponent {
        [[nodiscard]] virtual PlayerComponent* clone() const = 0;
        virtual void deleteBase() const {}
        virtual ~PlayerComponent() = default;

        /**
         * Check id_wisdom.txt for more information.
         */
        virtual const std::string& getTypeId() const = 0;


        /**
         * @return The component ID, not including type information (everything before the @)
         */
        std::string getStrippedId() const {
            const std::string& typeId = getTypeId();
            return typeId.substr(typeId.find('@'));
        }
    };
}


#endif //WARZONECIVILISATION_PLAYER_COMPONENT_H
