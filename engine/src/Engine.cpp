#include "Engine.h"

#include <iostream>
#include <OpenGL/gl3.h>

Engine::Engine(): window_(nullptr), running_(false), glContext_(nullptr) {}


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

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE
    );
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    window_ = SDL_CreateWindow(
        "Window",
        1920,
         1080,
        SDL_WINDOW_OPENGL
        );

    if (window_ == nullptr) {
        std::cout << "Failed to create window." << std::endl;
        return false;
    }

    glContext_ = SDL_GL_CreateContext(window_);
    SDL_GL_SetSwapInterval(1);
    glEnable(GL_MULTISAMPLE);
    if (glContext_ == nullptr) {
        std::cout << "Failed to create OpenGL context: "
                  << SDL_GetError() << std::endl;
        return false;
    }

    if (!renderer_.initialize()) {
        std::cout << "Failed to initialize renderer." << std::endl;
        return false;
    }

    glClearColor(0.08f, 0.08f, 0.10f, 1.0f);


    return true;
}

void Engine::run() {
    running_ = true;
    Uint64 previousCounter = SDL_GetPerformanceCounter();
    Uint64 frequency = SDL_GetPerformanceFrequency();

    while (running_) {
        processEvents();

        Uint64 currentCounter = SDL_GetPerformanceCounter();

        double deltaTime =
            static_cast<double>(currentCounter - previousCounter)
            / static_cast<double>(frequency);

        previousCounter = currentCounter;

        // std::cout << deltaTime << std::endl;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderer_.render();
        SDL_GL_SwapWindow(window_);

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
    std::cout << "Shutting down..." << std::endl;

    renderer_.shutdown();

    if (window_ != nullptr) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }

    if (glContext_ != nullptr) {
        SDL_GL_DestroyContext(glContext_);
        glContext_ = nullptr;
    }
    SDL_Quit();
}
