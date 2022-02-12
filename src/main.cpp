#include "shader.h" //you'd better include glad/glad.h before including GLFW/glfw3.h
#include <GLFW/glfw3.h>
#include <iostream>
#include "log.h"


// 窗口大小改变事件的回调函数
void framebuffer_size_callback(GLFWwindow * win, int width, int height) {
    glViewport(0, 0, width, height);
}

// 窗口处理键盘输入事件
void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

const char *vertexShaderSourcePath = "../shader/vertex_shader.txt";
const char *fragmentShaderSourcePath = "../shader/fragment_shader.txt";

GLFWwindow * createWindow(int width, int height, const char *title) {
    // 窗口属性设置
    Log log;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
    if(window == nullptr) {
        log.e("failed to create GLFW window");
        glfwTerminate();
        return nullptr;
    }
    log.i("window created");
    return window;
}


int main() {
    float vertexes[] = {
        // position         // color
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 顶部 
    };

    Log log;
    unsigned int vertex_buffer_object = 0;
    unsigned int vertex_array_object = 0;
    GLFWwindow *window = createWindow(800, 600, "learn openGL");

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        log.e("failed to initialize GLAD");
        return -1;
    }

    // 构造shader
    Shader shader(vertexShaderSourcePath, 
                fragmentShaderSourcePath);

    // 生成 VAO VBO
    glGenVertexArrays(1, &vertex_array_object);     // VAO
    glGenBuffers(1, &vertex_buffer_object);         // VBO
    log.i("VBO / VAO generated");

    // 绑定 VAO ：顶点数组对象
    glBindVertexArray(vertex_array_object);

    // 绑定 VBO 并复制数据到缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

    log.i("VAO / VBO buffer data binded");

    // 链接顶点属性 位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    log.i("vertex array attribute enabled");

    //使窗口循环显示
    while(!glfwWindowShouldClose(window)) {
       
        //处理输入
        processInput(window);
        //渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 激活自定义的 shader
        shader.use();

        // 绑定VAO
        glBindVertexArray(vertex_array_object);

        // 绘制
        glDrawArrays(GL_TRIANGLES, 0, 3);        // 使用顶点数组直接绘制
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);    // 使用顶点数组 索引 进行绘制

        
        //检查并调用事件，交换缓冲
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteBuffers(1, &vertex_buffer_object);

    glfwTerminate();

    return 0;
}
