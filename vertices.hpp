#ifndef _VERTICES_
#define _VERTICES_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::mat4 model(1.0f);
glm::mat4 view(1.0f);
glm::mat4 projection(1.0f);

float vertices[6][6][5] = {
    //{x, y, z, tex_x, tex_y}
    //first surface, green
    {
        {0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1},
        {1, 0, 0, 1, 0},

        {1, 1, 0, 1, 1},
        {0, 1, 0, 0, 1},
        {1, 0, 0, 1, 0},
    },
    //second surface, blue
    {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 0, 1},
        {1, 0, 1, 1, 0},

        {1, 1, 1, 1, 1},
        {0, 1, 1, 0, 1},
        {1, 0, 1, 1, 0},
    },
    //third surface, white
    {
        {0, 0, 0, 0, 0},
        {1, 0, 0, 0, 1},
        {0, 0, 1, 1, 0},

        {1, 0, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {0, 0, 1, 1, 0},
    },
    //fourth surface, yellow
    {
        {0, 1, 0, 0, 0},
        {1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0},

        {1, 1, 1, 1, 1},
        {1, 1, 0, 0, 1},
        {0, 1, 1, 1, 0},
    },
    //fifth surface, orange
    {
        {0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1},
        {0, 0, 1, 1, 0},

        {0, 1, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {0, 0, 1, 1, 0},
    },
    //sixth surface, red
    {
        {1, 0, 0, 0, 0},
        {1, 1, 0, 0, 1},
        {1, 0, 1, 1, 0},

        {1, 1, 1, 1, 1},
        {1, 1, 0, 0, 1},
        {1, 0, 1, 1, 0},
    },
};

#endif