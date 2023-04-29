#pragma once
#pragma once
#include "Geometry.h"

#include <glad/glad.h>

#include <array>

struct EnemyGeometry
{
    Geometry obj{
        Geometry::create<40, 24>(
    { //     COORDINATES     /   TexCoord  //
            //bottom
            0.0f, 0.0f, 0.5f,    1.0f, 0.0f,
            0.0f, 0.0f, -.5f,    0.0f, 0.0f,

            //top
            0.0f, 1.0f, 0.5f,    1.0f, 1.0f,
            0.0f, 1.0f, -.5f,    0.0f, 1.0f,
    },

    {
        0, 1, 2,
        2, 1, 3,
    })
    };
};