#ifndef WARZONECIVILISATION_OBJECT_COMPONENT_H
#define WARZONECIVILISATION_OBJECT_COMPONENT_H

#include <string>

namespace wzc {
    struct ObjectComponent {
        [[nodiscard]] virtual ObjectComponent* clone() const = 0;
        virtual ~ObjectComponent() = default;
        
        /**
         * Check id_wisdom.txt for more information.
         */
        virtual const std::string& getTypeId() const = 0;
        
        std::string getStrippedId() const {
            const std::string& typeId = getTypeId();
            return typeId.substr(typeId.find('@'));
        }
    };
}


#endif //WARZONECIVILISATION_OBJECT_COMPONENT_H
