#ifndef WARZONECIVILISATION_GAME_PLAYER_H
#define WARZONECIVILISATION_GAME_PLAYER_H

#include <string>

namespace wzc {
    /**
     * Deleted by Game.
     */
    struct GamePlayer {
        GamePlayer(const std::string& id, size_t turn);
        GamePlayer(const GamePlayer& other) = default;
        
        const std::string& getId() const;
        size_t getTurn() const;
        
        bool operator==(const GamePlayer& other) const;
    
    private:
        std::string id;
        size_t turn;
    };
}


#endif //WARZONECIVILISATION_GAME_PLAYER_H
