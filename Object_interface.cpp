#include <glad/glad.h>
#include"Object.h"

class Object_interface : public Object {
    virtual GLfloat* getVertices() const override;
    virtual GLuint* getIndices() const override;
};

GLfloat* Object_interface::getVertices() const {
    return vertices_;
};

GLuint* Object_interface::getIndices() const {
    return indices_;
};
