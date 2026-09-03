#pragma once
#include <array>
#include <OpenGL/gl3.h>

class Renderer {
    public:
    Renderer();
    ~Renderer();

    bool initialize();
    void render();
    void shutdown();

    private:
    std::array<float, 6> vertices_;

    GLuint vbo_;
    GLuint vao_;
    GLuint shaderProgram_;
};

