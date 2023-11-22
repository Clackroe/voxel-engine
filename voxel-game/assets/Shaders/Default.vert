


#version 330 core

layout (location = 0) in uint data;

out vec2 texCoord;


uniform samplerBuffer t_TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

#define BASE_17_WIDTH uint(17)
#define BASE_17_DEPTH uint(17)
#define BASE_17_HEIGHT uint(289)

#define POSITION_MASK uint(0x1FFFF)
#define TEX_ID_MASK uint(0x1FFE0000)
#define TEX_INDEX_MASK uint(0xE0000000)

void main()
{
    uint z = data % BASE_17_WIDTH;
	uint x = (data % BASE_17_HEIGHT) / BASE_17_DEPTH;
	uint y = (data - (x * BASE_17_DEPTH) - z) / BASE_17_HEIGHT;

    uint t_ID = (data & TEX_ID_MASK) >> 17;
    uint uv_INDEX = (data & TEX_INDEX_MASK) >> 29;

    int t_INDEX = int(t_ID) * 8 + int(uv_INDEX) * 2;
    
    vec2 tCoord;
    tCoord.x = texelFetch(t_TexCoords, t_INDEX + 0).r;
	tCoord.y = texelFetch(t_TexCoords, t_INDEX + 1).r;



    gl_Position = projection * view * model * vec4(float(x), float(y), float(z), 1.0);
    
    texCoord = tCoord;
}
