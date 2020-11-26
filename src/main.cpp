#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "ext/glew/glew.h"
#include "ext/GLFW/glfw3.h"
#include "ext/stbi/stb_image.h"

#include <iostream>
#include <string>

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(960, 720, 
    "The Global Pandemic", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
        return -1;

    float positions[] =
    {
        +0.5, +0.5,    1.0, 1.0, // 0
        +0.5, -0.5,    1.0, 0.0, // 1
        -0.5, -0.5,    0.0, 0.0, // 2
        -0.5, +0.5,    0.0, 1.0  // 3
    };

    unsigned int indices[] =
    {
        0, 1, 2, 0, 2, 3
    };

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    unsigned int va;
    glGenVertexArrays(1, &va);
    glBindVertexArray(va);

    unsigned int vb;
    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), 
    positions, GL_STATIC_DRAW);

    unsigned int ib;
    glGenBuffers(1, &ib);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), 
    indices, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 
    4 * sizeof(float), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 
    4 * sizeof(float), (void*)(2 * sizeof(float)));

    extern const char* VertexShader;
    extern const char* FragmentShader;

    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &VertexShader, 0);
    glCompileShader(vs);
    int vertex_compiled;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &vertex_compiled);
    if (vertex_compiled != GL_TRUE)
        std::cout << "FAILED: vertex" << std::endl;

    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &FragmentShader, 0);
    glCompileShader(fs);
    int fragment_compiled;
    glGetShaderiv(fs, GL_COMPILE_STATUS, &fragment_compiled);
    if (fragment_compiled != GL_TRUE)
        std::cout << "FAILED: fragment" << std::endl;

    unsigned int sr = glCreateProgram();
    glAttachShader(sr, vs);
    glAttachShader(sr, fs);
    glLinkProgram(sr);
    glUseProgram(sr);
    glDeleteShader(vs);
    glDeleteShader(fs);

    unsigned int tx;
    stbi_set_flip_vertically_on_load(1);
    int iwidth, iheight, ibpp;
    unsigned char* ibuffer = stbi_load("img/covid.png", 
    &iwidth, &iheight, &ibpp, 4);
    if (!ibuffer)
        std::cout << "Failed to load the texture!" << std::endl;
    glGenTextures(1, &tx);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tx);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, iwidth, iheight, 
    0, GL_RGBA, GL_UNSIGNED_BYTE, ibuffer);
    if (ibuffer)
        stbi_image_free(ibuffer);
    
    int location = glGetUniformLocation(sr, "u_Texture");
    glUniform1i(location, 0);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        //glClearColor(0.5, 0.1, 0.4, 1.0);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}