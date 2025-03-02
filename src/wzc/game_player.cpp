#include "game_player.h"

namespace wzc {
    GamePlayer::GamePlayer(const std::string& id, const size_t turn)
            : id(id), turn(turn) {}
    
    const std::string& GamePlayer::getId() const {
        return id;
    }
    
    size_t GamePlayer::getTurn() const {
        return turn;
    }
    
    bool GamePlayer::operator==(const GamePlayer& other) const {
        return turn == other.turn;
    }
}
