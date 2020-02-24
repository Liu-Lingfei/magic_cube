#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "magic_cube.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow *window);

void set_magic_cube_direction(float normal[][4]);
void rotate_cube_slowly();

void display_game_info();

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
const float NINETY_DEGREES = 90.0;

glm::vec3 cameraPos(0.0f, 0.0f, 1.0f);
glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float currFrame = 0.0f;
float lastFrame = 0.0f;
float lastx = SCR_WIDTH/2.0f;
float lasty = SCR_HEIGHT/2.0f;
float pitch = 0.0f;
float yaw = 0.0f;
bool firstMouse = true;

magic_cube *Cube;

int rotation_surface = -1;
int rotation_counter = 0;
float rotation_speed = 1.0f;

int main(void) {
    //glfw: intialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "magic_cube", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetKeyCallback(window, key_callback);

    //glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to inisitalize GLAD" << std::endl;
        return -1;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    display_game_info();

    Cube = new magic_cube();
    //render loop
    while (!glfwWindowShouldClose(window)) {
        currFrame = glfwGetTime();
        deltaTime = currFrame - lastFrame;
        lastFrame = currFrame;

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processInput(window);
        if (rotation_surface >= 0) rotate_cube_slowly();
        
        model = view = projection = glm::mat4(1.0f);
        model = glm::rotate(model, -glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));

        float normal[6][4] = {
            {0, 0, -1, 1}, //green
            {0, 0, 1, 1},  //blue
            {0, -1, 0, 1}, //white
            {0, 1, 0, 1},  //yellow
            {-1, 0, 0, 1}, //orange
            {1, 0, 0, 1},  //red
        };

        for (int t = 0; t < 6; ++t) {
            glm::vec4 temp(normal[t][0], normal[t][1], normal[t][2], normal[t][3]);
            temp = model * temp;
            for (int s = 0; s < 4; ++s) normal[t][s] = temp[s]/temp[3];
        }

        model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));

        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.0f));
        //view = glm::lookAt(cameraPos, cameraTarget, cameraUp);

        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/SCR_HEIGHT, 0.1f, 100.0f);

        set_magic_cube_direction(normal);
        Cube->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //glDeleteVertexArrays(27, VAO);
    //glDeleteBuffers(27, VBO);

    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    
    float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += cameraSpeed * (cameraPos - cameraTarget);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * (cameraPos - cameraTarget);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * glm::normalize(glm::cross(cameraPos - cameraTarget, cameraUp));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += cameraSpeed * glm::normalize(glm::cross(cameraPos - cameraTarget, cameraUp));
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}


void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastx = xpos;
        lasty = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastx;
    float yoffset = lasty - ypos;

    lastx = xpos;
    lasty = ypos;

    float sensibility = 0.05f;
    xoffset *= sensibility;
    yoffset *= sensibility;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 90.0f) {
        pitch = 90.0f;
    }
    if (pitch < -90.0f) {
        pitch = -90.0f;
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action != GLFW_PRESS) return;
    if (rotation_surface >= 0) return;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS &&
        glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) != GLFW_PRESS) {
        rotation_speed = 1.0f;
    }
    else {
        rotation_speed = -1.0f;
    }
    switch (key) {
        case GLFW_KEY_U:
            rotation_surface = Cube->up;
            break;
        case GLFW_KEY_D:
            rotation_surface = Cube->oppo[Cube->up];
            break;
        case GLFW_KEY_R:
            rotation_surface = Cube->right;
            break;
        case GLFW_KEY_L:
            rotation_surface = Cube->oppo[Cube->right];
            break;
        case GLFW_KEY_F:
            rotation_surface = Cube->front;
            break;
        case GLFW_KEY_B:
            rotation_surface = Cube->oppo[Cube->front];
            break;
        default:
            break;
    }
}

void set_magic_cube_direction(float normal[][4]) {
    int right_color = RED, up_color = YELLOW, front_color = BLUE;

    float up_max = 0, right_max = 0, front_max = 0;

    for (int i = 0; i < 6; ++i) {
        if (normal[i][2] < 0) continue;
        else if (normal[i][1] > up_max) {
            up_color = i;
            up_max = normal[i][1];
        }
    }
    for (int i = 0; i < 6; ++i) {
        if (normal[i][2] < 0 || i == up_color) continue;
        else if (normal[i][0] > right_max) {
            right_color = i;
            right_max = normal[i][0];
        }
    }
    for (int i = 0; i < 6; ++i) {
        if (normal[i][2] < 0 || i == up_color || i == right_color) continue;
        else if (normal[i][2] > front_max) {
            front_color = i;
            front_max = normal[i][2];
        }
    }
    Cube->set_direction(right_color, up_color, front_color);
}

void rotate_cube_slowly() {
    if (rotation_surface == Cube->up)
        Cube->U(rotation_speed);
    else if (rotation_surface == Cube->oppo[Cube->up])
        Cube->D(rotation_speed);
    else if (rotation_surface == Cube->right)
        Cube->R(rotation_speed);
    else if (rotation_surface == Cube->oppo[Cube->right])
        Cube->L(rotation_speed);
    else if (rotation_surface == Cube->front)
        Cube->F(rotation_speed);
    else if (rotation_surface == Cube->oppo[Cube->front])
        Cube->B(rotation_speed);

    rotation_counter++;
    if (rotation_counter == NINETY_DEGREES) {
        rotation_counter = 0;
        rotation_surface = -1;
    }
}

void display_game_info() {
    printf("\n\nWelcome to my first OpenGL game: rubic_cube!!!\n\n"

        "Hints:\n"
        "(1) Esc to quit\n"
        "(2) mouse for changing view\n"
        "(3) keyboard for rotating the cube clockwise:\n"
        "    U(p)  D(own)  F(ront)  B(ack)  R(ight)  L(eft)\n"
        "(4) hit Shift at the same time to rotate anti-clockwise\n\n"

        "Enjoy yourself :)\n");
}