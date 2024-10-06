#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//Shader source code strings
const char *vertex_shader_str =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 outColor;\n"
    "\n"
    "void main() {\n"
    "  gl_Position = vec4(aPos, 1.0);\n"
    "  outColor = aColor;\n"
    "}\0";

const char *fragment_shader_str =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 outColor;\n"
    "\n"
    "void main() {\n"
    "  FragColor = vec4(outColor, 1.0f);\n"
    "}\0";

/**
 * Function that maps an 8 byte hex color value to a floating
 * point number between 0 and 1.
 *
 *
 * Why don't they just use the hex code tho.
 */
float hex_to_float(unsigned char hex) {
    return (float)hex / (float)0xFF;
}

int main(void) {

    //Init GLFW subsystem and configure GLFW context
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false); //Prevent window resizing as I don't want to deal with it

    //Create GLFW window instance
    GLFWwindow *window = glfwCreateWindow(640, 480, "Mi triangulo asombroso", NULL, NULL);
    if (window == NULL) {
        printf("Error occured during window initialization. Exiting...\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glViewport(0, 0, 640, 480);

    //Triangle vertices
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Do vertex shader compilation
    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_str, NULL);
    glCompileShader(vertex_shader);

    //Check if shader compilation was successful.
    int success;
    char info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        printf("Error compiling OpenGL shader. Exiting...\n");
        printf("Error string: %s\n", info_log);
        glfwTerminate();
        return -1;
    }

    //Do fragment shader compilation
    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_str, NULL);
    glCompileShader(fragment_shader);

    //Check if shader compilation was successful
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        printf("Error compiling OpenGL shader. Exiting...\n");
        printf("Error string: %s\n", info_log);
        glfwTerminate();
        return -1;
    }

    //Create shader program
    unsigned int shader_program;
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    //Check linking status
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        printf("Error linking shader program. Exiting...\n");
        printf("Error string: %s\n", info_log);
        glfwTerminate();
        return -1;
    }

    glUseProgram(shader_program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Render loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(hex_to_float(0x36), hex_to_float(0x45), hex_to_float(0x4F), 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}