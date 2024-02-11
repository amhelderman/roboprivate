#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>




// Vertex Shader source
const GLchar* vertexShaderSrc = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal; // Normal to pass to fragment shader
out vec3 FragPos; // Position of the fragment

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0)); // Calculate position
    Normal = mat3(transpose(inverse(model))) * aNormal; // Transform normals
    
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)glsl";

// Fragment Shader source
const GLchar* fragmentShaderSrc = R"glsl(
#version 330 core
out vec4 FragColor;

in vec3 Normal; // Normal from vertex shader
in vec3 FragPos; // Position of the fragment

uniform vec3 lightDir; // Direction of the light
uniform vec3 lightColor; // Color of the light
uniform vec3 objectColor; // Color of the object

void main()
{
    // Ambient light
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    // Diffuse light
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, normalize(-lightDir)), 0.0);
    vec3 diffuse = diff * lightColor;
    
    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}

)glsl";

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Cube", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }

    // Define the viewport dimensions
    glViewport(0, 0, 800, 600);

    // Vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
    glCompileShader(vertexShader);

    // Fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, nullptr);
    glCompileShader(fragmentShader);


    // Check for compilation errors in shaders 
    GLint success;
    GLchar infoLog[512];

    // After compiling each shader
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }




    // Link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // After linking the shader program
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Set up vertex data and buffers and configure vertex attributes
GLfloat vertices[] = {
    // Positions            // Normals
    // Back face
    -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f, // Bottom-left
     0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f, // top-right
     0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f, // bottom-right         
     0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f, // top-right
    -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f, // bottom-left
    -0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f, // top-left
    // Front face
    -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f, // bottom-left
     0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f, // bottom-right
     0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f, // top-right
     0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f, // top-right
    -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f, // top-left
    -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f, // bottom-left
    // Other faces...
};

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0); // Position attribute

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1); // Normal attribute

    


    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 



    // Before the render loop
glm::vec3 lightDir = glm::vec3(-0.2f, -1.0f, -0.3f);
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 objectColor = glm::vec3(1.0f, 0.5f, 0.31f);

// Pass them to the shader
glUseProgram(shaderProgram);
unsigned int lightDirLoc = glGetUniformLocation(shaderProgram, "lightDir");
unsigned int lightColorLoc = glGetUniformLocation(shaderProgram, "lightColor");
unsigned int objectColorLoc = glGetUniformLocation(shaderProgram, "objectColor");

glUniform3fv(lightDirLoc, 1, glm::value_ptr(lightDir));
glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));
glUniform3fv(objectColorLoc, 1, glm::value_ptr(objectColor));






    // Render loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));




        // Draw the cube
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}
