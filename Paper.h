#pragma once
#include "Geometry.h"

#include <glad/glad.h>

#include <array>
#include <string>

struct PaperGeometry
{
    Geometry obj{ Geometry::create<20, 6>(
    { //     COORDINATES     /        COLORS      /   TexCoord  //
            //bottom
            0.42f, 0.0f, 0.0f, 0.0f, 0.0f, //0
            0.0f, 0.0f, 0.0f, 1.0f, 0.0f,  //1
            0.0f, 0.0f, 0.6f, 1.0f, 1.0f,  //2
            0.42f, 0.0f, 0.6f, 0.0f, 1.0f, //3

    },
    {
        0, 1, 2,
        0, 2, 3,
    }
    )
    };
};