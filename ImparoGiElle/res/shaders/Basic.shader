#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal;

uniform mat4 u_MVP;

out vec4 Normal;

void main()
{
   gl_Position = u_MVP * position;
   Normal = normal;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 Normal;

uniform vec4 u_Color;

void main()
{
	float d = dot(Normal, normalize(vec4(1, 1, 1, 1)));
	color = (u_Color * d) + (vec4(0.6, 0.4, 0.4, 1)*(1-d));
};