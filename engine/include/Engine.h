#pragma once

#include <SDL3/SDL.h>


class Engine {
    public:
    Engine();
    ~Engine();
    bool initialize();
    void run();

    private:
    void processEvents();
    void shutdown();

    SDL_Window* window_;
    bool running_;
    SDL_GLContext glContext_;


};



