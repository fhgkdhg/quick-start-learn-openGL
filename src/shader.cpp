#include "shader.h"


Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
    std::string vertexSourceCode;
    std::string fragmentSourceCode;
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;
    Log log;
    

    // 保证 ifstream 对象可以抛出异常
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vertexShaderFile.open(vertexShaderPath);
        fragmentShaderFile.open(fragmentShaderPath);
        std::stringstream vertexShaderStream, fragmentShaderStream;

        // 读取文件到流中
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        // 关闭文件
        vertexShaderFile.close();
        fragmentShaderFile.close();

        // 将数据流转换为字符串
        vertexSourceCode = vertexShaderStream.str();
        fragmentSourceCode = fragmentShaderStream.str();
    } catch(std::ifstream::failure) {
        log.e("Error: Shader - failed to read file");
    }

    compileShader(vertexSourceCode, fragmentSourceCode);
}


Shader::~Shader() {
    glDeleteProgram(id);
}

// 编译着色器
void Shader::compileShader(const std::string &vertexSourceCode, const std::string &fragmentSourceCode) {
    unsigned int vertexShader, fragmentShader;
    int successFlag;
    char loginfo[512];
    Log log;
    const char *vCode = vertexSourceCode.c_str();
    const char *fCode = fragmentSourceCode.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vCode, nullptr);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successFlag);
    if(!successFlag) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, loginfo);
        log.e("Error: Shader - vertex shader compilation failed");
        log.e(loginfo);
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fCode, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successFlag);
    if(!successFlag) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, loginfo);
        log.e("Error: Shader - fragment shader compilation failed");
        log.e(loginfo);
    }

    // 链接两个着色器
    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &successFlag);
    if(!successFlag) {
        glGetProgramInfoLog(id, 512, nullptr, loginfo);
        log.e("Error: Shader - program link failed");
        log.e(loginfo);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() const {
    glUseProgram(id);
}


void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
