#ifndef WARZONECIVILISATION_EVENT_H
#define WARZONECIVILISATION_EVENT_H

#include <cstdint>
#include <stdexcept>

namespace wzc {
    struct Game;
    struct GameState;
    
    struct Event {
        explicit Event(GameState* game) : game(game), cancelled(false) {}
        
        virtual const std::string& getTypeId() const = 0;
        virtual ~Event() = default;
        
        GameState* const game;

        bool cancelled;
    };
    
    struct EventError : std::runtime_error {
        EventError() : std::runtime_error("An event error occurred") {}
        explicit EventError(const std::string& what) : std::runtime_error(what) {}
        
        virtual const std::string& getTypeId() const = 0;
        
        // event only becomes available after it is returned by GameState
        Event* getEvent() const { return event; }
        
        ~EventError() override { delete event; }
        
    private:
        Event* event = nullptr;
        friend Game;
    };
}

#endif //WARZONECIVILISATION_EVENT_H
