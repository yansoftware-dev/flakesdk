#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>


namespace Datatypes {
    struct EmptyObject {
        std::string name = "EmptyObject";
        
        glm::vec3 position{0.0f};
        glm::vec3 rotation{0.0f};
        glm::vec3 scale{1.0f};

        glm::mat4 getTransform() const {
            glm::mat4 transform{1.0f};

            transform = glm::translate(transform, position); // Position on XYZ
            transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1, 0, 0)); // Rotation on X
            transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0, 1, 0)); // Rotation on Y
            transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0, 0, 1)); // Rotation on Z
            transform = glm::scale(transform, scale); // Scale on XYZ

            return transform;
        }

        void setPosition(float x, float y, float z) { position = glm::vec3(x, y ,z); }
        void setRotation(float x, float y, float z) { rotation = glm::vec3(x, y, z); }
        void setScale(float x, float y, float z) { scale = glm::vec3(x, y ,z); }
    };
}