#pragma once
#include <array>
#include <OpenGl/gl3.h>

class Renderer {
    public:
    Renderer();
    ~Renderer();

    bool initialize();
    void render();
    void shutdown();

    private:
    std::array<float, 16> vertices_;

    GLuint vbo_;
    GLuint vao_;
    GLuint shaderProgram_;
};

