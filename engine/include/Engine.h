#pragma once

#include <SDL3/SDL.h>
#include "Renderer.h"


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

    Renderer renderer_;

};



