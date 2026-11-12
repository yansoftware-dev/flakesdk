#pragma once

#include "vertex.h"

namespace Datatypes {
    struct Mesh {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        
        void makeTriangle() {
            vertices = {
                {{-0.5f,-0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, }, // 0
                {{ 0.5f,-0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, }, // 1
                {{ 0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, }  // 2
            };
            indices = {
                0, 1, 2
            };
        }

        void makeQuad() {
            vertices = {
                {{-0.5f,-0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, }, // 0
                {{ 0.5f,-0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, }, // 1
                {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, }, // 2
                {{ 0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 0.0f}, }  // 3
            };  
            indices = {
                0, 1, 2, // Triangle 1
                1, 3, 2  // Triangle 2 
            };
        }

        void makeCube() {
            vertices = {
                {{-0.5f,-0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}}, // 0 front bottom left
                {{ 0.5f,-0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}}, // 1 front bottom right
                {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}, // 2 front top left
                {{ 0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 1.0f}}, // 3 front top right
                {{-0.5f,-0.5f,-0.5f}, {0.0f, 1.0f, 1.0f}}, // 4 back bottom left
                {{ 0.5f,-0.5f,-0.5f}, {1.0f, 0.0f, 1.0f}}, // 5 back bottom right
                {{-0.5f, 0.5f,-0.5f}, {1.0f, 1.0f, 0.0f}}, // 6 back top left
                {{ 0.5f, 0.5f,-0.5f}, {0.0f, 1.0f, 0.0f}}, // 7 back top right
            };
            indices =  {
                0, 1, 2, 1, 3, 2, // Front face
                4, 5, 6, 5, 7, 6, // Back face
                4, 0, 6, 0, 2, 6, // Left face
                5, 1, 7, 1, 3, 7, // Right face
                6, 2, 7, 2, 3, 7, // Top face
                4, 0, 5, 0, 1, 5, // Bottom face
            };
        }
    };
}