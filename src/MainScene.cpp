#include "Scenes/MainScene.h"

void MainScene::update () {
    float cameraSpeed = 0.05f;
	if (keypress (GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, GL_TRUE);

    if (keypress (GLFW_KEY_W)) {
        cameraPos += cameraSpeed * cameraFront;
        cameraUpdated = true;
    }

    if (keypress (GLFW_KEY_S)) {
        cameraPos -= cameraSpeed * cameraFront;
        cameraUpdated = true;
    }

    if (keypress (GLFW_KEY_A)) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        cameraUpdated = true;
    }

    if (keypress (GLFW_KEY_D)) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        cameraUpdated = true;
    }

    if (keypress (GLFW_KEY_LEFT_SHIFT)) {
        cameraPos += cameraSpeed * cameraUp;
        cameraUpdated = true;
    }

    if (keypress (GLFW_KEY_LEFT_CONTROL)) {
        cameraPos -= cameraSpeed * cameraUp;
        cameraUpdated = true;
    }

    if (cameraUpdated) {
        view = glm::lookAt (cameraPos, cameraPos+cameraFront, cameraUp);
        projection = glm::perspective(glm::radians(fov), (GLfloat) Scene::window_width / (GLfloat) Scene::window_height, 0.1f, 100.0f);  

        glUniformMatrix4fv (viewLoc, 1, GL_FALSE, glm::value_ptr (view));
        glUniformMatrix4fv (projLoc, 1, GL_FALSE, glm::value_ptr (projection));
    }
}

void MainScene::setupScene () {
    Object<BasicShapes::Cube>* cube = new Object<BasicShapes::Cube> ();
    cube->setShader(shader);

    Object<BasicShapes::Floor>* floor = new Object<BasicShapes::Floor> ();
    floor->setShader(shader);
    floor->setScale (glm::vec3 (3.5f, 3.5f, 3.5f));
    floor->setTranslation(glm::vec3(0.0f, 0.35f, 0.0f));

    view = glm::lookAt (cameraPos, cameraPos+cameraFront, cameraUp);

    push_object (cube);
    push_object (floor);
}

glm::vec3 MainScene::cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 MainScene::cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 MainScene::cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float MainScene::lastX = MAXFLOAT;
float MainScene::lastY = MAXFLOAT;
float MainScene::yaw = 0.0f;
float MainScene::pitch = 0.0f;
float MainScene::roll = 0.0f;
bool MainScene::cameraUpdated = false;

void MainScene::mouse_callback (GLFWwindow* window, double xpos, double ypos) {
    if (lastX == MAXFLOAT || lastY == MAXFLOAT) {
        lastX = xpos;
        lastY = ypos;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);

    cameraUpdated = true;
}

float MainScene::fov = 35.0f;

void MainScene::scroll_callback (GLFWwindow *window, double xoffset, double yoffset) {
    if (fov >= 1.0f && fov <= 45.0f) fov -= yoffset;
    if (fov <= 1.0f) fov = 1.0f;
    if (fov >= 45.0f) fov = 45.0f;

    cameraUpdated = true;
}
