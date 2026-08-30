#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_video.h>

int main() {
    std::cout << "Engine Starting..." << std::endl;

    SDL_Window *window;
    bool done = false;

    SDL_Init(SDL_INIT_VIDEO);
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "SDL failed to initialize: "
                  << SDL_GetError() << std::endl;
        return 1;
    }

    window = SDL_CreateWindow(
        "Window",
        640,
        480,
        SDL_WINDOW_OPENGL
        );

    if (window == nullptr) {
        std::cout << "Failed to create window." << std::endl;
        return 1;
    }

    while (!done) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}