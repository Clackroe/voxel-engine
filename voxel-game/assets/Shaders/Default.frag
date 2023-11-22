#version 330 core

out vec4 FragColor;

in vec2 texCoord;
uniform sampler2D tex;

void main()
{
    FragColor = vec4(1.0,0.2,0.2,1.0);//texture(tex, texCoord); 
}