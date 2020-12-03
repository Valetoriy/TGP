const char* VertexShader = 
R"sh(
#version 460

in layout(location = 0) vec4 position;
in layout(location = 1) vec2 texposition;
uniform mat4 u_MVP;
out vec2 o_texposition;

void main()
{
    gl_Position = u_MVP * position;
    o_texposition = texposition;
}

)sh";

const char* FragmentShader = 
R"sh(
#version 460

uniform sampler2D u_Texture;
in vec2 o_texposition;
out vec4 color;

void main()
{
    color = texture(u_Texture, o_texposition);
}

)sh";