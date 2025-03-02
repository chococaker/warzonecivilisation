#ifndef WARZONECIVILISATION_GAME_H
#define WARZONECIVILISATION_GAME_H

#include <deque>
#include <vector>

#include "game_type_map.h"

#include "handle/player_handle.h"
#include "handle/object_handle.h"
#include "ecs/component/handle/player_component_handle.h"
#include "ecs/component/handle/object_component_handle.h"
#include "ecs/system/system.h"

struct tagMTRand;

namespace wzc {
    struct Event;
    struct EventError;
    
    struct GameState;
    
    struct GameInitialiser {
    
    };
    
    struct Game {
        Game(TileTypeMap* tileTypeMap, const GameInitialiser& initialiser);
        
        const GameState& getState() const;
        
        void pushEvent(Event* event); // takes ownership of event
        void removeEvent(size_t index); // removes this event and all future events
        void removeLastEvent();
        
        void clearDeque();
        
        // execute all events & delete events
        // if there is an error through execution, all events executed will be deleted
        // including that event that caused the error
        void nextTurn();

        tagMTRand* getRand() const;
        
        PlayerHandle asHandle(const GamePlayer& player);
        ObjectHandle asHandle(const GameObject& object);
        PlayerComponentHandle asHandle(const GamePlayer& owner, const PlayerComponent& component);
        ObjectComponentHandle asHandle(const GameObject& owner, const ObjectComponent& component);
        
        ~Game();
    
    private:
        std::deque<Event*> eventDeque;
        TileTypeMap* tileTypeMap;
        
        GameState* gameState;
        size_t currentTurn;
        GameState* stagedGameState; // gameState being accessed by handles during an event staging

        std::vector<System*> systems;
        
        tagMTRand* rand; // games will always be on the same thread

        void propagate(Event* ev) const;
        
        friend struct PlayerComponentHandle;
        friend struct ObjectComponentHandle;
        friend struct PlayerHandle;
        friend struct ObjectHandle;
    };
}


#endif // WARZONECIVILISATION_GAME_H
