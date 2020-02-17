#include <stdio.h>

static int surface[6][3][3];
enum COLOR {GREEN, BLUE, WHITE, YELLOW, ORANGE, RED,
            GREEN_T, BLUE_T, WHITE_T, YELLOW_T, ORANGE_T, RED_T};

class magic_cube
{
private:
    static void cw(int color);
public:
    int right;  //to x direction
    int up;     //to y direction
    int front;  //to z direction
    COLOR oppo[6];
    void (*rotate[12])(void);

    void set_direction(int r, int u, int f);

    magic_cube();
    static void yellow();
    static void white_t();
    static void red();
    static void orange_t();
    static void blue();
    static void green_t();

    static void yellow_t();
    static void white();
    static void red_t();
    static void orange();
    static void blue_t();
    static void green();

    void U();
    void Dt();
    void R();
    void Lt();
    void F();
    void Bt();

    void Ut();
    void Rt();
    void Ft();
    void D();
    void L();
    void B();
};

magic_cube::magic_cube() {
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 3; ++j)
            for (int k = 0; k < 3; ++k)
                surface[i][j][k] = i;
    oppo[WHITE] = YELLOW;
    oppo[YELLOW] = WHITE;
    oppo[ORANGE] = RED;
    oppo[RED] = ORANGE;
    oppo[GREEN] = BLUE;
    oppo[BLUE] = GREEN;

    right = RED;
    up = YELLOW;
    front = BLUE;

    rotate[YELLOW] = this->yellow;
    rotate[WHITE] = this->white;
    rotate[RED] = this->red;
    rotate[ORANGE] = this->orange;
    rotate[BLUE] = this->blue;
    rotate[GREEN] = this->green;

    rotate[YELLOW_T] = this->yellow_t;
    rotate[WHITE_T] = this->white_t;
    rotate[RED_T] = this->red_t;
    rotate[ORANGE_T] = this->orange_t;
    rotate[BLUE_T] = this->blue_t;
    rotate[GREEN_T] = this->green_t;
}

void magic_cube::U() {
    rotate[up]();
}

void magic_cube::D() {
    rotate[oppo[up]]();
}

void magic_cube::R() {
    rotate[right]();
}

void magic_cube::L() {
    rotate[oppo[right]]();
}

void magic_cube::F() {
    rotate[front]();
}

void magic_cube::B() {
    rotate[oppo[front]]();
}

void magic_cube::Ut() {
    rotate[up + 6]();
}

void magic_cube::Dt() {
    rotate[oppo[up] + 6]();
}

void magic_cube::Rt() {
    rotate[right + 6]();
}

void magic_cube::Lt() {
    rotate[oppo[right] + 6]();
}

void magic_cube::Ft() {
    rotate[front + 6]();
}

void magic_cube::Bt() {
    rotate[oppo[front] + 6]();
}


void magic_cube::set_direction(int right_color, int up_color, int front_color) {
    right = right_color;
    up = up_color;
    front = front_color;
}

void magic_cube::cw(int color) {
    int temp;

    temp = surface[color][0][1];
    surface[color][0][1] = surface[color][1][0];
    surface[color][1][0] = surface[color][2][1];
    surface[color][2][1] = surface[color][1][2];
    surface[color][1][2] = temp;

    temp = surface[color][0][0];
    surface[color][0][0] = surface[color][2][0];
    surface[color][2][0] = surface[color][2][2];
    surface[color][2][2] = surface[color][0][2];
    surface[color][0][2] = temp;
}

void magic_cube::yellow() {
    cw(YELLOW);

    int temp[3];
    for (int i = 0; i < 3; ++i) {
        temp[i] = surface[RED][i][2];
        surface[RED][i][2] = surface[GREEN][0][2 - i];
        surface[GREEN][0][2 - i] = surface[ORANGE][2 - i][2];
        surface[ORANGE][2 - i][2] = surface[BLUE][0][i];
        surface[BLUE][0][i] = temp[i];
    }
}

void magic_cube::white_t() {
    cw(WHITE);

    int temp[3];
    for (int i = 0; i < 3; ++i) {
        temp[i] = surface[RED][i][0];
        surface[RED][i][0] = surface[GREEN][2][2 - i];
        surface[GREEN][2][2 - i] = surface[ORANGE][2 - i][0];
        surface[ORANGE][2 - i][0] = surface[BLUE][2][i];
        surface[BLUE][2][i] = temp[i];
    }
}

void magic_cube::red() {
    cw(RED);

    int temp[3];
    for (int i = 0; i < 3; ++i) {
        temp[i] = surface[BLUE][i][2];
        surface[BLUE][i][2] = surface[WHITE][2 - i][2];
        surface[WHITE][2 - i][2] = surface[GREEN][2 - i][2];
        surface[GREEN][2 - i][2] = surface[YELLOW][i][2];
        surface[YELLOW][i][2] = temp[i];
    }
}

void magic_cube::orange_t() {
    cw(ORANGE);

    int temp[3];
    for (int i = 0; i < 3; ++i) {
        temp[i] = surface[BLUE][i][0];
        surface[BLUE][i][0] = surface[WHITE][2 - i][0];
        surface[WHITE][2 - i][0] = surface[GREEN][2 - i][0];
        surface[GREEN][2 - i][0] = surface[YELLOW][i][0];
        surface[YELLOW][i][0] = temp[i];
    }
}

void magic_cube::blue() {
    cw(BLUE);

    int temp[3];
    for (int i = 0; i < 3; ++i) {
        temp[i] = surface[YELLOW][2][i];
        surface[YELLOW][2][i] = surface[ORANGE][0][i];
        surface[ORANGE][0][i] = surface[WHITE][2][2 - i];
        surface[WHITE][2][2 - i] = surface[RED][0][2 - i];
        surface[RED][0][2 - i] = temp[i];
    }
}

void magic_cube::green_t() {
    cw(GREEN);

    int temp[3];
    for (int i = 0; i < 3; ++i) {
        temp[i] = surface[YELLOW][0][i];
        surface[YELLOW][0][i] = surface[ORANGE][2][i];
        surface[ORANGE][2][i] = surface[WHITE][0][2 - i];
        surface[WHITE][0][2 - i] = surface[RED][2][2 - i];
        surface[RED][2][2 - i] = temp[i];
    }
}

void magic_cube::yellow_t() {
    for (int i = 0; i < 3; ++i) yellow();
}

void magic_cube::red_t() {
    for (int i = 0; i < 3; ++i) red();
}

void magic_cube::blue_t() {
    for (int i = 0; i < 3; ++i) blue();
}

void magic_cube::white() {
    for (int i = 0; i < 3; ++i) white_t();
}

void magic_cube::orange() {
    for (int i = 0; i < 3; ++i) orange_t();
}

void magic_cube::green() {
    for (int i = 0; i < 3; ++i) green_t();
}
