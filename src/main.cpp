#include <Engine.h>
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_video.h>

int main() {

    Engine engine;

    if (!engine.initialize()) {
        return 1;
    }
    engine.run();

    return 0;
}