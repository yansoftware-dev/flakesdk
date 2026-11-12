#include "renderer.h"

#include <iostream>
#include <algorithm>
#include <type_traits>
#include <array>

using namespace Flake;

void RenderServer::initialize()
{   // Enable depth_test.
    glEnable(GL_DEPTH_TEST);

    // Generate Buffers and Arrays.
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Binding and setting up data for buffers.
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 10000, 0, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 10000, 0, GL_DYNAMIC_DRAW);

    // Inform OpenGL on how the data is made.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Datatypes::Vertex), (void*)offsetof(Datatypes::Vertex, position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Datatypes::Vertex), (void*)offsetof(Datatypes::Vertex, color_rgb));
    glEnableVertexAttribArray(2);
    glVertexAttribIPointer(2, 1, GL_INT, sizeof(Datatypes::Vertex), reinterpret_cast<void*>(offsetof(Datatypes::Vertex, model_id)));

    Flake::File default_vert_shader;
    Flake::File default_frag_shader;
    default_vert_shader.path = std::string("src/flake_engine/graphics/shaders/default_vertex_shader.glsl");
    default_frag_shader.path = std::string("src/flake_engine/graphics/shaders/default_fragment_shader.glsl");

    m_default_shader.vertex_shader_file = default_vert_shader;
    m_default_shader.fragment_shader_file = default_frag_shader;

    m_default_shader.load();

    // ...
}

void RenderServer::setRenderMode(RenderMode mode)
{   
    if (mode == RenderMode::NORMAL) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } else if (mode == RenderMode::WIREFRAME) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        std::cout << "Non-existent render mode selected. --> Using RenderMode::NORMAL." << std::endl; 
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void RenderServer::setCameraProjection(glm::mat4 projection) { m_camera_projection = projection; }

void RenderServer::setCameraTransform(glm::mat4 transform) {m_camera_transform = transform; }

void RenderServer::addToQueue(Datatypes::MeshObject& object) { m_render_queue.push_back(&object); }

void RenderServer::clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void RenderServer::render()
{      
    clear();  

    v_data.clear();
    e_data.clear();

    if (m_render_queue.empty()) { return; }

    std::vector<glm::mat4> model;
    glm::mat4 view, projection;

    uint32_t total_prev_vert_count = 0;
    uint32_t model_id = 0;
    for (auto* object : m_render_queue) {
        for (Datatypes::Vertex v : object->mesh.vertices) {
            v.model_id = model_id;

            v_data.push_back(v);
        }

        for (uint32_t e : object->mesh.indices) { 
            uint32_t edited_e = e + total_prev_vert_count;
            e_data.push_back(edited_e);
        }

        model.push_back(object->getTransform());

        total_prev_vert_count += (uint32_t)object->mesh.vertices.size();
        model_id++;
    }


    view = m_camera_transform;
    projection = m_camera_projection;

    m_default_shader.use();

    int modelLoc = glGetUniformLocation(m_default_shader.ID, "model[0]");
    glUniformMatrix4fv(modelLoc, (GLuint)model.size(), GL_FALSE, glm::value_ptr(model.front()));
    int viewLoc = glGetUniformLocation(m_default_shader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    int projectionLoc = glGetUniformLocation(m_default_shader.ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, v_data.size() * sizeof(Datatypes::Vertex), (void*)v_data.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, e_data.size() * sizeof(uint32_t), (void*)e_data.data(), GL_DYNAMIC_DRAW);

    //glDrawArrays(GL_TRIANGLES, 0, (GLuint)v_data.size());
    glDrawElements(GL_TRIANGLES, (GLuint)e_data.size(), GL_UNSIGNED_INT, nullptr);
}