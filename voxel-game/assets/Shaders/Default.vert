


#version 330 core

layout (location = 0) in uint data;
layout (location = 2) in vec2 tPos;

out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

#define BASE_17_WIDTH uint(17)
#define BASE_17_DEPTH uint(17)
#define BASE_17_HEIGHT uint(289)

void main()
{
    uint z = data % BASE_17_WIDTH;
	uint x = (data % BASE_17_HEIGHT) / BASE_17_DEPTH;
	uint y = (data - (x * BASE_17_DEPTH) - z) / BASE_17_HEIGHT;
  

    gl_Position = projection * view * model * vec4(float(x), float(y), float(z), 1.0);
    
    texCoord = tPos;
}
