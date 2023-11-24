// shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in float pointSize;

void main()
{
    gl_Position = position;
    gl_PointSize = pointSize;
}

// shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_color;

void main()
{
    color = u_color;
}
