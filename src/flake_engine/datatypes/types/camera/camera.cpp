#include "camera.h"

#include <iostream>
#include <algorithm>

using namespace Datatypes;

// - Set up variables
glm::vec3 cam_up    = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cam_front = glm::vec3(0.0f, 0.0f,-1.0f);
glm::vec3 cam_right = glm::vec3(1.0f, 0.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void Camera::update()
{      
    const float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    const float speed = freecam_speed * deltaTime;
    const bool looking = glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;

    if (looking) {
        glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        updateMouseLook();

        glm::vec3 flatFront = glm::normalize(glm::vec3(cam_front.x, 0.0f, cam_front.z));
        glm::vec3 flatRight = glm::normalize(glm::cross(flatFront, worldUp_));

        if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS)
            position += flatFront * speed;
        if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS)
            position -= flatFront * speed;
        if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
            position -= flatRight * speed;
        if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
            position += flatRight * speed;
        if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_PRESS)
            position += worldUp_ * speed;
        if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            position -= worldUp_ * speed;
    } else {
        glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstMouse_ = true;
    }
}

void Camera::updateMouseLook()
{
    double mouseX, mouseY;
    glfwGetCursorPos(glfwGetCurrentContext(), &mouseX, &mouseY);

    if (firstMouse_) {
        lastMouseX_ = mouseX;
        lastMouseY_ = mouseY;
        firstMouse_ = false;
        return;
    }

    const float xOffset = static_cast<float>(mouseX - lastMouseX_);
    const float yOffset = static_cast<float>(lastMouseY_ - mouseY);

    lastMouseX_ = mouseX;
    lastMouseY_ = mouseY;

    yaw_ += xOffset * freecam_sensitivity;
    pitch_ += yOffset * freecam_sensitivity;

    pitch_ = std::clamp(pitch_, -89.0f, 89.0f);

    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    glm::vec3 direction;
    direction.x = std::cos(glm::radians(yaw_)) *
                  std::cos(glm::radians(pitch_));
    direction.y = std::sin(glm::radians(pitch_));
    direction.z = std::sin(glm::radians(yaw_)) *
                  std::cos(glm::radians(pitch_));

    cam_front = glm::normalize(direction);
    cam_right = glm::normalize(glm::cross(cam_front, worldUp_));
    cam_up = glm::normalize(glm::cross(cam_right, cam_front));
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + cam_front, cam_up);
}