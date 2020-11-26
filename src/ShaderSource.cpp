const char* VertexShader = 
R"sh(
#version 330 core

in layout(location = 0) vec4 position;
//in layout(location = 1) vec2 texposition;
//out vec2 o_texposition;

void main()
{
    gl_Position = position;
    //o_texposition = texposition;
}

)sh";

const char* FragmentShader = 
R"sh(
#version 330 core

//uniform sampler2D u_Texture;
//in vec2 o_texposition;
out vec4 color;

void main()
{
    color = vec4(0.0, 1.0, 0.0, 1.0);
}

)sh";