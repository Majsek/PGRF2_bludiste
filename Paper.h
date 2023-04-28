#pragma once
#include "Geometry.h"

#include <glad/glad.h>

#include <array>
#include <string>

struct PaperGeometry
{
    Geometry obj{ Geometry::create<20, 6>(
    { //     COORDINATES       /    TexCoord  //
            //bottom
            0.41f, 0.0f, 0.2f,   0.0f, 0.0f, //0
            0.2f, 0.0f, 0.2f,    1.0f, 0.0f,  //1
            0.2f, 0.0f, 0.5f,    1.0f, 1.0f,  //2
            0.41f, 0.0f, 0.5f,   0.0f, 1.0f, //3
    },
    {
        0, 1, 2,
        0, 2, 3,
    }
    )
    };
};