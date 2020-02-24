#ifndef _MAGIC_CUBE_
#define _MAGIC_CUBE_

#include "stb_image.hpp"
#include "shader_s.hpp"
#include "vertices.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <assert.h>
#include <cmath>

char colors[6][16] = {
    "green.png", "blue.png", "white.png", "yellow.png", "orange.png", "red.png"
};

char texName[6][16] = {
    "texture0", "texture1", "texture2", "texture3", "texture4", "texture5"
};

class cube {
    private:
    void refresh_vbo();

    public:
    float v[6][6][5];
    unsigned int VAO, VBO;

    cube();
    void init_vao(unsigned int vao, unsigned int vbo);
    void draw(Shader *shader, unsigned int texture[]);
    void move(float dx, float dy, float dz);
    void rotate(float axis[], float degree);
};

cube::cube() {
    memcpy(v, vertices, sizeof(vertices));
}

void cube::rotate(float axis[], float degree) {
    glm::mat4 model(1.0f);
    //旋转角度是逆时针，取负变为顺时针
    model = glm::rotate(model, glm::radians(-degree), glm::vec3(axis[0], axis[1], axis[2]));

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            glm::vec4 point(v[i][j][0],
                            v[i][j][1],
                            v[i][j][2], 1.0f);
            point = model * point;
            //for (int m = 0; m < 3; ++m) printf("%f, ", point[m]);
            //printf("\n");
            for (int m = 0; m < 3; ++m) v[i][j][m] = point[m];
        }
    }
    refresh_vbo();
}

void cube::move(float dx, float dy, float dz) {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            v[i][j][0] += dx;
            v[i][j][1] += dy;
            v[i][j][2] += dz;
        }
    }
    refresh_vbo();
}

void cube::init_vao(unsigned int vao, unsigned int vbo) {
    VAO = vao;
    VBO = vbo;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_DYNAMIC_DRAW);
    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);


}

void cube::refresh_vbo() {
    //注意：在修改bufferdata前需要绑定buffer
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
}

void cube::draw(Shader *shader, unsigned int texture[]) {
    glBindVertexArray(VAO);
    for (int j = 0; j < 6; ++j) {
        //printf("j = %d\n", j);
        glActiveTexture(GL_TEXTURE0 + j);
        glBindTexture(GL_TEXTURE_2D, texture[j]);

        shader->use();
        unsigned int index = glGetUniformLocation(shader->ID, "index");
        unsigned int modelLoc = glGetUniformLocation(shader->ID, "model");
        unsigned int viewLoc = glGetUniformLocation(shader->ID, "view");
        unsigned int projectionLoc = glGetUniformLocation(shader->ID, "projection");
        glUniform1i(index, j);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        //绘制三角形
        glDrawArrays(GL_TRIANGLES, j*6, 6);
    }
}

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

class magic_cube {
public:
    int right;  //to x direction
    int up;     //to y direction
    int front;  //to z direction
    SURFACE_INDEX oppo[6];
    //float cubes[27][6][6][5];
    Shader *shader;
    cube cubes[27];
    unsigned int VAO[27], VBO[27];
    unsigned int texture[6];

    magic_cube();

    void draw();
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
    glGenVertexArrays(27, VAO);
    glGenBuffers(27, VBO);
    for (int i = 0; i < 27; ++i) cubes[i].init_vao(VAO[i], VBO[i]);

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
                cubes[k*9+j*3+i].move((float)i - 1.5, (float)j - 1.5, (float)k - 1.5);
            }
        }
    }

    //load and create a texture
    glGenTextures(6, texture);

    for (int i = 0; i < 6; i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, texture[i]);
        //set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //load image, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(colors[i], &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }

    //build and compile out shader program
    shader = new Shader("shader.vs", "shader.fs");

    for (int i = 0; i < 6; i++) {
        shader->use();
        shader->setInt(texName[i], i);
    }
    glEnable(GL_DEPTH_TEST);
}

void magic_cube::draw() {
    for (int i = 0; i < 27; ++i) cubes[i].draw(shader, texture);
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
                if (at_same_position(cubes[cube_index].v[i][j], cubes[center_index].v[color_index][k])) {
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
        cubes[cube_index[i]].rotate(axis, degree);
    }
}

void magic_cube::rotate_surface(int surface_index, float degree) {
    int surface_cube[9];
    int count = 0;

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

#endif