#include <iostream>
#include <string>
#include <math.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../../shaders/shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../img/stb_image.h"

using namespace std;

/* Prototypes */
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

/* Main */
int main()
{
    cout << "Run Main()" << endl;

    /* GLFW 초기화 */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    /* Window object 생성 */
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Shaders", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to creat GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* Initialize GLAD */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    /// Shader Settings
    string dirPath = "./Desktop/Refer/OpenGL/shaders/";
    string vertexPath = dirPath + "5.1.transform.vs";
    string fragmentPath = dirPath + "5.1.transform.fs";
    Shader ourShader(vertexPath.c_str(), fragmentPath.c_str());

    /* Set up vertex & index data */
    float vertices[] = {
        // positions            // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f   // top left
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    // float texCoords[] = {
    //     0.0f, 0.0f, // lower-left corner
    //     1.0f, 0.0f, // lower-right corner
    //     0.5f, 1.0f  // top-center corner
    // };

    /* Set up buffers */
    unsigned int VBO, VAO, EBO;

    // Generate & Bind VBO, VAO, EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Copy vertices array in a buffer for OpenGL to use
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Linking vertex attributes pointers
    // 위치값 attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // 텍스처 좌표값 attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // glVertexAttribPointer()를 통해서 vertex attribute의 vertex buffer object를 가져왔기 때문에, unbind가 가능함
    // 그러나 VAO가 활성화 되어 있는 동안 EBO는 unbind 하면 안됨
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    /// ------------------------------------
    /// Texture Settings
    unsigned int texture1, texture2;
    // textue1
    glGenTextures(1, &texture1);            // texture object를 생성하기 위한 id를 생성
    glBindTexture(GL_TEXTURE_2D, texture1); // texture object를 type에 맞게 바인딩
    // texture wrapping/filtering 옵션 설정
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     // x축 wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     // y축 wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // 축소될 때 어떻게 filtering할 것인지
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // 확대될 때 어떻게 filtering할 것인지
    // image 로드, 생성
    string dirImgPath = "./Desktop/Refer/OpenGL/img/";
    string imgPath = dirImgPath + "container.jpg";
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // stb_image.h에 의해 이미지가 y축 반전되어 로드되기 때문에, 이를 방지하기 위해 y축 반전

    unsigned char *data = stbi_load(imgPath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); // texture object에 image data를 넣음
        glGenerateMipmap(GL_TEXTURE_2D);                                                          // texture object에 대한 mipmap을 생성
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data); // image data를 메모리에서 해제

    // textue2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // texture wrapping/filtering 옵션 설정
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // image 로드, 생성
    string imgPath2 = dirImgPath + "awesomeface.png";
    data = stbi_load(imgPath2.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        // png 파일은 투명도를 가지고 있기 때문에, RGBA로 설정
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data); // image data를 메모리에서 해제

    // OpenGL에게 각각의 texture unit에 대한 texture object를 지정
    ourShader.use();
    // glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0); // texture unit 0을 사용하는 texture1 uniform에 0을 할당
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    // ------------------------------------
    /* Render Loop */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // texture 바인딩
        // glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE0); // texture unit 0을 활성화
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1); // texture unit 1을 활성화
        glBindTexture(GL_TEXTURE_2D, texture2);

        // transformations
        glm::mat4 trans = glm::mat4(1.0f); // 단위 행렬(identity matrix)로 초기 설정
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        // trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::scale(trans, glm::vec3(0.5, 0.7, 0.8));

        // shader.h를 통해서 shaderProgram을 활성화
        ourShader.use();
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Optional: De-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    // glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

/* Functions */
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
