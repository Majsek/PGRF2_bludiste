#pragma once
#include <glad/glad.h>

struct Object {

    GLfloat* vertices_;
    GLuint* indices_;

    virtual GLfloat* getVertices() const = 0;
    virtual GLuint* getIndices() const = 0;

};