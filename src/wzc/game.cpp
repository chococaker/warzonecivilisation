#include "game.h"
#include "ecs/system/event/event.h"
#include "ecs/system/event/start_event.h"
#include "ecs/system/event/end_event.h"
#include "game_state.h"
#include "wzc/ecs/ecs_manager.h"
#include "game_player.h"
#include "game_object.h"
#include "ecs/component/player/player_component.h"
#include "ecs/component/entity/object_component.h"

#include "mtwister/mtwister.h"

#include <cassert>

namespace wzc {
    Game::Game(TileTypeMap* tileTypeMap, const GameInitialiser& initialiser)
            : tileTypeMap(tileTypeMap), currentTurn(0) {
        rand = new tagMTRand();
        gameState = new GameState(tileTypeMap, rand, 0, this);
        stagedGameState = nullptr;
        
        // TODO: init game
    }
    
    void Game::pushEvent(Event* event) {
        eventDeque.push_back(event);
    }
    
    void Game::removeEvent(size_t index) {
        if (index >= eventDeque.size() - 1) clearDeque();
        for (size_t i = eventDeque.size() - index; i < eventDeque.size(); i++) {
            delete eventDeque.back();
            eventDeque.pop_back();
        }
    }
    
    void Game::removeLastEvent() {
        eventDeque.pop_back();
    }
    
    void Game::clearDeque() {
        for (const Event* event : eventDeque) {
            delete event;
        }
        
        eventDeque.clear();
    }
    
    Game::~Game() {
        while (!eventDeque.empty()) {
            delete eventDeque.back();
            eventDeque.pop_back();
        }
        
        delete rand;
    }
    
    const GameState& Game::getState() const {
        return *gameState;
    }
    
    void Game::nextTurn() {
        assert(gameState != nullptr);
        
        GameState* nextState = new GameState(*gameState);
        
        size_t& nextStateTurn = nextState->currentTurn;
        if (nextStateTurn == nextState->getPlayerCount() - 1) {
            nextStateTurn = 0;
        } else {
            nextStateTurn++;
        }

        const EcsManager* ecsManager = nextState->ecsManager;
        assert(ecsManager != nullptr);
        
        Event* startEvent = new StartEvent(gameState);
        
        try {
            ecsManager->propagate(startEvent);
        } catch (EventError& e) {
            e.event = startEvent;
            throw;
        }
        
        while (!eventDeque.empty()) {
            Event* event = eventDeque.front();
            eventDeque.pop_front();
            
            try {
                ecsManager->propagate(event);
            } catch (EventError& e) {
                e.event = event;
                throw;
            }
            
            delete event;
        }
        
        Event* endEvent = new EndEvent(gameState);
        
        try {
            ecsManager->propagate(endEvent);
        } catch (EventError& e) {
            e.event = endEvent;
            throw;
        }
        
        delete gameState;
        gameState = nextState;
    }
    
    tagMTRand* Game::getRand() const {
        return rand;
    }
    
    PlayerHandle Game::asHandle(const GamePlayer& player) {
        return {player.getId(), this};
    }
    
    ObjectHandle Game::asHandle(const GameObject& object) {
        return {object.getId(), this};
    }
    
    PlayerComponentHandle Game::asHandle(const std::string& owner, const PlayerComponent& component) {
        return {owner, component.getTypeId(), this};
    }
    
    ObjectComponentHandle Game::asHandle(const std::string& owner, const ObjectComponent& component) {
        return {owner, component.getTypeId(), this};
    }
}
