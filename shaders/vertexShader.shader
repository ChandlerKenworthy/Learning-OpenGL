#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float rightOffset;
out vec3 ourColor;
out vec3 outPos;

void main()
{
    outPos = vec3(aPos.x + rightOffset, aPos.y, aPos.z);
    gl_Position = vec4(aPos.x + rightOffset, aPos.y, aPos.z, 1.0);
    ourColor = aColor;
}