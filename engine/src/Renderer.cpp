#include "Renderer.h"

#include <iostream>

const char* vertexShaderSource = R"(
    #version 410 core

    layout(location = 0) in vec2 position;

    void main() {
        gl_Position = vec4(position, 0.0, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 410 core

    out vec4 color;

    void main() {
        color = vec4(0.2, 0.7, 1.0f, 1.0);
    }
)";

Renderer::Renderer():
    vertices_{
    0.0f, 0.5f,
    -0.5f, -0.5f,
    0.5f, -0.5f
    },
    vbo_(0),
    vao_(0),
    shaderProgram_(0) {

}


bool Renderer::initialize() {

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[512];

        glGetShaderInfoLog(
            vertexShader,
            512,
            nullptr,
            infoLog);

        std::cout << "Vertex shader compilation failed: " << infoLog << std::endl;
        return false;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];

        glGetShaderInfoLog(
            fragmentShader,
            512,
            nullptr,
            infoLog);

        std::cout << "Fragment shader compilation failed: " << infoLog << std::endl;
        return false;
    }

    shaderProgram_ = glCreateProgram();
    glAttachShader(shaderProgram_, vertexShader);
    glAttachShader(shaderProgram_, fragmentShader);
    glLinkProgram(shaderProgram_);

    glGetProgramiv(shaderProgram_, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];

        glGetProgramInfoLog(
            shaderProgram_,
            512,
            nullptr,
            infoLog);

        std::cout << "Program linking failed: " << infoLog << std::endl;
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;

}

void Renderer::render() {
    glUseProgram(shaderProgram_);
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0 ,3);
}

void Renderer::shutdown() {
    if (vao_ != 0) {
        glDeleteVertexArrays(1, &vao_);
        vao_ = 0;
    }

    if (vbo_ != 0) {
        glDeleteBuffers(1, &vbo_);
        vbo_ = 0;
    }

    if (shaderProgram_ != 0) {
        glDeleteProgram(shaderProgram_);
        shaderProgram_ = 0;
    }
}

Renderer::~Renderer() {
}
