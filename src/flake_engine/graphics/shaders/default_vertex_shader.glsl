#version 330 core

const int MAX_MODEL_COUNT = 64;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in int aModelID;

out vec3 vColor;

uniform mat4 model[MAX_MODEL_COUNT];
uniform mat4 view;
uniform mat4 projection;

void main() 
{
    vColor = aColor;
    int index = int(aModelID);
    gl_Position = projection * view * model[index] * vec4(aPos, 1.0);
}