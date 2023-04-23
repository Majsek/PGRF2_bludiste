#pragma once
#include <glad/glad.h>
#include "Object_interface.cpp"

class Wall : public Object_interface {
    Wall() {
        vertices_ = new GLfloat[12]{ 0.0f, 0.0f, 0.0f,
                                    1.0f, 0.0f, 0.0f,
                                    1.0f, 1.0f, 0.0f,
                                    0.0f, 1.0f, 0.0f };
        indices_ = new GLuint[6]{ 0, 1, 2, 0, 2, 3 };
    }

public:
    ~Wall() {
        delete[] vertices_;
        delete[] indices_;
    }
};
