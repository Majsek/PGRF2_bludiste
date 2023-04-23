#pragma once
#include "Geometry.h"

#include <glad/glad.h>

#include <array>

struct WallGeometry
{
    Geometry obj{
        Geometry::create<40, 24>(
    { //     COORDINATES     /        COLORS      /   TexCoord  //
            //bottom
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

            1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

            //top
            0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    },

    {
        0, 1, 4,
        1, 5, 4,

        7, 3, 0,
        0, 4, 7,

        2, 3, 7,
        2, 7, 6,

        1, 2, 6,
        6, 5, 1,
    })
    };
};
