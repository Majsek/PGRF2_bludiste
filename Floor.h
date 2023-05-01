#pragma once
#include "Geometry.h"

#include <glad/glad.h>

#include <array>

struct FloorGeometry
{
    Geometry obj{
        Geometry::create<40, 24>(
    { //     COORDINATES     /   TexCoord  //
            //bottom
            0.0f, 0.0f, 0.0f,    15.0f, 0.0f,
            0.0f, 0.0f, 20.0f,    0.0f, 0.0f,

            //top
            20.0f, 0.0f, 0.0f,    15.0f, 15.0f,
            20.0f, 0.0f, 20.0f,    0.0f, 15.0f,
    },

    {
        0, 1, 2,
        2, 1, 3,
    })
    };
};
