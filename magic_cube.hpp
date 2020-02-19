#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assert.h>
#include <cmath>
#include "vertices.hpp"

enum SURFACE_INDEX {GREEN, BLUE, WHITE, YELLOW, ORANGE, RED,
            GREEN_T, BLUE_T, WHITE_T, YELLOW_T, ORANGE_T, RED_T};

enum CETER_INDEX {GREEN_CENTER = 4, BLUE_CENTER = 22,
                  WHITE_CENTER = 10, YELLOW_CENTER = 16,
                  ORANGE_CENTER = 12, RED_CENTER = 14};

int center_index[6] = {GREEN_CENTER, BLUE_CENTER,
                       WHITE_CENTER, YELLOW_CENTER,
                       ORANGE_CENTER, RED_CENTER};

float surface_normal[6][3] = {
    {0, 0, -1}, //green
    {0, 0, 1},  //blue
    {0, -1, 0}, //white
    {0, 1, 0},  //yellow
    {-1, 0, 0}, //orange
    {1, 0, 0},  //red
};

bool at_same_position(float p1[], float p2[]) {
    for (int i = 0; i < 3; ++i) if (abs(p1[i] - p2[i]) >= 0.0001) return false;
    return true;
}

class magic_cube
{
public:
    int right;  //to x direction
    int up;     //to y direction
    int front;  //to z direction
    SURFACE_INDEX oppo[6];
    float cubes[27][6][6][5];

    magic_cube();

    void set_direction(int r, int u, int f);
    bool is_at_same_surface(int cube_index, int center_index, int color_index);
    void rotate_cubes(int cube_index[], int num, float axis[], float degree);
    void rotate_surface(int surface_index, float degree);

    void U(float degree);
    void D(float degree);
    void R(float degree);
    void L(float degree);
    void F(float degree);
    void B(float degree);
};

magic_cube::magic_cube() {
    oppo[WHITE] = YELLOW;
    oppo[YELLOW] = WHITE;
    oppo[ORANGE] = RED;
    oppo[RED] = ORANGE;
    oppo[GREEN] = BLUE;
    oppo[BLUE] = GREEN;

    right = RED;
    up = YELLOW;
    front = BLUE;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                memcpy(cubes[k*9+j*3+i], vertices, sizeof(vertices));
                for (int p = 0; p < 6; ++p) {
                    for (int q = 0; q < 6; ++q) {
                        cubes[k*9+j*3+i][p][q][0] += i;
                        cubes[k*9+j*3+i][p][q][1] += j;
                        cubes[k*9+j*3+i][p][q][2] += k;

                        cubes[k*9+j*3+i][p][q][0] -= 1.5;
                        cubes[k*9+j*3+i][p][q][1] -= 1.5;
                        cubes[k*9+j*3+i][p][q][2] -= 1.5;
                    }
                }
            }
        }
    }
}

void magic_cube::set_direction(int right_color, int up_color, int front_color) {
    right = right_color;
    up = up_color;
    front = front_color;
}

bool magic_cube::is_at_same_surface(int cube_index, int center_index, int color_index) {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            for (int k = 0; k < 4; ++k) {
                if (at_same_position(cubes[cube_index][i][j], cubes[center_index][color_index][k])) {
                    return true;
                }
            }
        }
    } 
    return false;
}

void magic_cube::rotate_cubes(int cube_index[], int num, float axis[], float degree) {
    glm::mat4 model(1.0f);
    //旋转角度是逆时针，取负变为顺时针
    model = glm::rotate(model, glm::radians(-degree), glm::vec3(axis[0], axis[1], axis[2]));

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 6; ++j) {
            for (int k = 0; k < 6; ++k) {
                glm::vec4 point(cubes[cube_index[i]][j][k][0],
                                cubes[cube_index[i]][j][k][1],
                                cubes[cube_index[i]][j][k][2], 1.0f);
                point = model * point;
                for (int m = 0; m < 3; ++m) cubes[cube_index[i]][j][k][m] = point[m];
            }
        }
    }
}

void magic_cube::rotate_surface(int surface_index, float degree) {
    int surface_cube[9];
    int count = 0;
    bool checked;

    for (int i = 0; i < 9; ++i) surface_cube[i] = -1;

    for (int i = 0; i < 27; ++i) {
        if (is_at_same_surface(i, center_index[surface_index], surface_index)) {
            surface_cube[count++] = i;
        }
    }
    //旋转面必有9个块
    assert(count == 9);

    rotate_cubes(surface_cube, count, surface_normal[surface_index], degree);
}

void magic_cube::U(float degree) {
    rotate_surface(up, degree);
}

void magic_cube::D(float degree) {
    rotate_surface(oppo[up], degree);
}

void magic_cube::R(float degree) {
    rotate_surface(right, degree);
}

void magic_cube::L(float degree) {
    rotate_surface(oppo[right], degree);
}

void magic_cube::F(float degree) {
    rotate_surface(front, degree);
}

void magic_cube::B(float degree) {
    rotate_surface(oppo[front], degree);
}