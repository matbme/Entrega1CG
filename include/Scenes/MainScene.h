#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

#include "Scene.h"

class MainScene : public Scene {
public:
    MainScene (GLuint width, GLuint height, std::string window_name)
        : Scene (width, height, window_name)
    {
        // Disables mouse cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  

        glfwSetCursorPosCallback (window, MainScene::mouse_callback);  
        glfwSetScrollCallback (window, MainScene::scroll_callback);
    }

    void update () override;
    void setupScene () override;

    static void mouse_callback (GLFWwindow *window, double xpos, double ypos);
    static void scroll_callback (GLFWwindow* window, double xoffset, double yoffset);

    static bool cameraUpdated;

    static glm::vec3 cameraPos;
    static glm::vec3 cameraFront;
    static glm::vec3 cameraUp;

    static float lastX, lastY;
    static float yaw, pitch, roll;

    static float fov;
};

#endif
