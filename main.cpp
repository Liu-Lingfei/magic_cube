#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assert.h>

#include "stb_image.hpp"
#include "shader_s.hpp"
#include "vertices.hpp"
#include "magic_cube.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow *window);
void show_hints();

void set_magic_cube_direction(float normal[][4]);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

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

magic_cube Cube;

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "magic_cube_0.9", NULL, NULL);
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

    //build and compile out shader program
    Shader ourShader = Shader("shader.vs", "shader.fs");

    unsigned int VAO[6], VBO[6];
    glGenVertexArrays(6, VAO);
    glGenBuffers(6, VBO);

    for (int i = 0; i < 6; i++) {
        glBindVertexArray(VAO[i]);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[i]), vertices[i], GL_STATIC_DRAW);
        //position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
    }

    //load and create a texture
    unsigned int texture[6];
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
    
    for (int i = 0; i < 6; i++) {
        ourShader.use();
        ourShader.setInt(texName[i], i);
    }
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    show_hints();
    //render loop
    while (!glfwWindowShouldClose(window)) {
        currFrame = glfwGetTime();
        deltaTime = currFrame - lastFrame;
        lastFrame = currFrame;

        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        for (int i = 0; i < 6; i++) {

            glBindVertexArray(VAO[i]);

            float t = glfwGetTime();

            glm::mat4 model(1.0f);

            //注意：交换两次旋转变换的位置，效果不一样
            //后执行的变化，即写在前面的这次变换拥有更高的优先级。就等于说是第一步的变换执行之后，被第二步变换改变了
            model = glm::rotate(model, -glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));

            //set the direction vector of each surface
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
            set_magic_cube_direction(normal);

            model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));
            model = glm::translate(model, glm::vec3(-1.5, -1.5, -1.5));

            glm::mat4 view(1.0f);
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1.0f));
            //view = glm::lookAt(cameraPos, cameraTarget, cameraUp);

            glm::mat4 projection(1.0f);
            projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/SCR_HEIGHT, 0.1f, 100.0f);

            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < 3; ++k) {
                    glActiveTexture(GL_TEXTURE0 + surface[i][j][k]);
                    glBindTexture(GL_TEXTURE_2D, texture[surface[i][j][k]]);

                    ourShader.use();
                    unsigned int index = glGetUniformLocation(ourShader.ID, "index");
                    unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
                    unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
                    unsigned int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");
                    glUniform1i(index, surface[i][j][k]);
                    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
                    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
                    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
                    //绘制三角形
                    glDrawArrays(GL_TRIANGLES, (3 * j + k) * 6, 6);
                }
            }
        }
        //std::cout << "yaw = " << yaw << ", pitch = " << pitch << std::endl;
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(6, VAO);
    glDeleteBuffers(6, VBO);

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
    //仔细看看这两个公式，可以让相机绕着目标旋转
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
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS &&
        glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) != GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_U:
                Cube.U();
                break;
            case GLFW_KEY_D:
                Cube.D();
                break;
            case GLFW_KEY_R:
                Cube.R();
                break;
            case GLFW_KEY_L:
                Cube.L();
                break;
            case GLFW_KEY_F:
                Cube.F();
                break;
            case GLFW_KEY_B:
                Cube.B();
                break;
            default:
                break;
        }
    }
    else {
        switch (key) {
            case GLFW_KEY_U:
                Cube.Ut();
                break;
            case GLFW_KEY_D:
                Cube.Dt();
                break;
            case GLFW_KEY_R:
                Cube.Rt();
                break;
            case GLFW_KEY_L:
                Cube.Lt();
                break;
            case GLFW_KEY_F:
                Cube.Ft();
                break;
            case GLFW_KEY_B:
                Cube.Bt();
                break;
            default:
                break;
        }
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        ;
    }
}

void set_magic_cube_direction(float normal[][4]) {
    int right_color, up_color, front_color;

    float up_max = 0, right_max = 0, front_max = 0;

    for (int i = 0; i < 6; ++i) {
        //只有normal[i][2] > 0才能被看到
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
    Cube.set_direction(right_color, up_color, front_color);
}

void show_hints() {
    printf("Welcome to Liu Lingfei's magic_cube game!!!\n\n");
    printf("Esc to quit\n");
    printf("Use mouse to 改变视角\n");
    printf("X = (U)p, (D)own, (R)ight, (L)eft, (F)ront, (B)ack to 顺时针旋转魔方\n");
    printf("shift+X to 逆时针旋转魔方\n");
}