#pragma once

#include <glad/glad.h>
#include "../datatypes/datatypes.h"

namespace Flake {

    enum RenderMode 
    {
        NORMAL, WIREFRAME
    };

    class RenderServer 
    {
    public:
        void initialize();
        void setRenderMode(RenderMode mode);
        void render();
        void clear();
        void addToQueue(Datatypes::MeshObject& object);
        void setCameraProjection(glm::mat4 projection);
        void setCameraTransform(glm::mat4 transform);
    private:
        const uint32_t MAX_MESH_OBJECTS = 64;

        std::vector<Datatypes::MeshObject*> m_render_queue;
        GLuint VAO, VBO, EBO;
        
        std::vector<Datatypes::Vertex> v_data;
        std::vector<uint32_t> e_data;

        Datatypes::Shader m_default_shader;

        glm::mat4 m_camera_projection{0};
        glm::mat4 m_camera_transform{0};
    };
}