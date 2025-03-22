#include "game.h"
#include "ecs/system/event/event.h"
#include "ecs/system/event/start_event.h"
#include "ecs/system/event/end_event.h"
#include "game_state.h"
#include "game_player.h"
#include "game_object.h"
#include "ecs/component/player/player_component.h"
#include "ecs/component/entity/object_component.h"

#include "mtwister/mtwister.h"

#include <algorithm>
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
        for (const Event* event: eventDeque) {
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

        // init next state with appropriate data
        GameState* nextState = new GameState(*gameState);

        size_t& nextStateTurn = nextState->currentTurn;
        if (nextStateTurn == nextState->getPlayerCount() - 1) {
            nextStateTurn = 0;
        } else {
            nextStateTurn++;
        }

        // propagate beginning event
        Event* startEvent = new StartEvent();
        try {
            propagate(startEvent, nextState);
        } catch (EventError& e) {
            delete startEvent;
            e.event = startEvent;
            throw;
        }

        delete startEvent;

        // propagate actual events
        while (!eventDeque.empty()) {
            Event* event = eventDeque.front();
            eventDeque.pop_front();

            try {
                propagate(event, nextState);
            } catch (EventError& e) {
                e.event = event;
                throw;
            }

            delete event;
        }


        // propagate ending event
        Event* endEvent = new EndEvent();
        try {
            propagate(endEvent, nextState);
        } catch (EventError& e) {
            delete startEvent;
            e.event = endEvent;
            throw;
        }

        delete endEvent;

        // clean up post-event game state
        //  1. remove objects marked for destruction
        std::vector<GameObject>& objects = gameState->objects;
        objects.erase(std::remove_if(
                          objects.begin(), objects.end(),
                          [](const GameObject& o) { return o.markedForDestruction; }),
                      objects.end());

        // clear garbage
        delete gameState;
        gameState = nextState;
    }

    void Game::propagate(Event* ev, GameState* gameState) const {
        for (const System* system: systems) {
            assert(system != nullptr);

            system->handle(ev, gameState);
        }
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

    PlayerComponentHandle Game::asHandle(const GamePlayer& owner, const PlayerComponent& component) {
        return {asHandle(owner), component.getTypeId(), this};
    }

    ObjectComponentHandle Game::asHandle(const GameObject& owner, const ObjectComponent& component) {
        return {asHandle(owner), component.getTypeId(), this};
    }
}
