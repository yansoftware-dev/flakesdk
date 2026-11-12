#pragma once 

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

namespace Datatypes {
    struct Vertex {
        glm::vec3 position;
        glm::vec3 color_rgb;
        uint32_t model_id; 
        //unsigned int texture_id;
    };
};