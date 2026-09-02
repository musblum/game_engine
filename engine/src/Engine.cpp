#include "Engine.h"

#include <iostream>

Engine::Engine(): window_(nullptr), running_(false) {}


Engine::~Engine() {
    shutdown();
}

bool Engine::initialize() {


    std::cout << "Engine Starting..." << std::endl;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "SDL failed to initialize: "
                  << SDL_GetError() << std::endl;
        return false;
    }

    window_ = SDL_CreateWindow(
        "Window",
        640,
        480,
        SDL_WINDOW_OPENGL
        );

    if (window_ == nullptr) {
        std::cout << "Failed to create window." << std::endl;
        return false;
    }
    return true;
}

void Engine::run() {
    running_ = true;
    while (running_) {
        processEvents();
    }
}

void Engine::processEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running_ = false;
            }
            if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_ESCAPE) {
                    running_ = false;
                }
                if (event.key.key == SDLK_SPACE) {
                    std::cout << "Space Pressed" << std::endl;
                }
            }
        }
}

void Engine::shutdown() {

    if (window_ != nullptr) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
        std::cout << "Shutting down..." << std::endl;
    }
    SDL_Quit();
}
