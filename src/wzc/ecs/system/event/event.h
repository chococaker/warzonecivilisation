#pragma once

#include <stdexcept>

namespace wzc {
    struct Game;
    struct GameState;
    
    struct Event {
        Event() : cancelled(false) {}
        
        virtual const std::string& getTypeId() const = 0;
        virtual ~Event() = default;

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
