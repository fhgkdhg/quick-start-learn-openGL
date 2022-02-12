#ifndef __SHADER_H_
#define __SHADER_H_

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "log.h"


class Shader {
    public:
    unsigned int id;
    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    ~Shader();
    void use() const;

    //uniform 工具函数
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name ,int value) const;
    void setFloat(const std::string &name, float value) const;

    private:
    void compileShader(const std::string &vertexCode, const std::string &fragmentCode);
};


#endif