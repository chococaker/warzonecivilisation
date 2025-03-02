#ifndef WARZONECIVILISATION_MOVABLE_COMPONENT_H
#define WARZONECIVILISATION_MOVABLE_COMPONENT_H

#include <vector>
#include <cstdint>
#include "wzc/ecs/component/entity/object_component.h"

namespace ccaker {
    struct MovableComponent final : wzc::ObjectComponent {
        MovableComponent(uint16_t maxDistancePerFullMove,
                         const std::vector<uint8_t> &traversableTileTypes,
                         double amountMovedThisTurn = 0);

        [[nodiscard]] double getAmountMovedThisTurn() const;

        [[nodiscard]] double getAmountLeft() const;

        [[nodiscard]] bool exceedsLimit(double more = 0) const;

        void addAmountMoved(double amount);

        void subtractAmountMoved(double amount);

        void resetAmountMoved();

        [[nodiscard]] ObjectComponent *clone() const override;

        uint16_t maxDistancePerFullMove;
        std::vector<uint8_t> traversableTileTypes;

        static const std::string ID;

        const std::string &getTypeId() const override {
            return ID;
        }

    private:
        double amountMovedThisTurn;
    };
}


#endif //WARZONECIVILISATION_MOVABLE_COMPONENT_H
