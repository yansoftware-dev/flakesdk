#pragma once

#include "../empty_object.h"

namespace Datatypes {
    struct Camera : EmptyObject {
    public:
        float fov = 90.0f;
        float near_plane = 0.01f;
        float far_plane = 1000.0f;

        float freecam_speed = 2.5f; // - default
        float freecam_sensitivity = 0.25f; // - default
        bool free_cam = false;

        glm::mat4 getProjection() {
            return glm::perspective(glm::radians(fov), 800.0f / 600.0f, near_plane, far_plane);
        }
        glm::mat4 getViewMatrix() const;

        void update();
        void setFieldOfView(float newfov) { fov = newfov; }
        void setFarNearPlane(float far, float near) { far_plane = far; near_plane = near; }
        void setFreeCamera(bool yesorno) { free_cam = yesorno; }
        void setFreeCameraSpeed(float speed) { freecam_speed = speed; }
        void setFreeCameraSensitivity(float sens) { freecam_sensitivity = sens; }

    private:
        void updateMouseLook();
        void updateCameraVectors();

        glm::vec3 worldUp_ = glm::vec3(0.0f, 1.0f, 0.0f);

        float yaw_ = -90.0f;
        float pitch_ = 0.0f;

        bool firstMouse_ = true;
        double lastMouseX_ = 0.0;
        double lastMouseY_ = 0.0;
    };
}