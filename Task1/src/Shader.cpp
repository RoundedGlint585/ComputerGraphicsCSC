//
// Created by roundedglint585 on 8/1/19.
//

#include "../include/Shader.h"
#include <iostream>

Shader::Shader(const std::string & vertexShaderData, const std::string & fragmentShaderData) : shaderID_(-1) {
    uint32_t vertexShader = compileVertexShader(vertexShaderData);
    uint32_t fragmentShader = compileFragmentShader(fragmentShaderData);
    linkShader(vertexShader, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

uint32_t Shader::compileVertexShader(const std::string &vertexShaderData) {
    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderSource = vertexShaderData.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    return vertexShader;
}

uint32_t Shader::compileFragmentShader(const std::string & fragmentShaderData) {
    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSource = fragmentShaderData.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    int success;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    return fragmentShader;
}

void Shader::linkShader(uint32_t vertexShader, uint32_t fragmentShader) {
    shaderID_ = glCreateProgram();
    glAttachShader(shaderID_, vertexShader);
    glAttachShader(shaderID_, fragmentShader);
    glLinkProgram(shaderID_);
    int success;
    glGetShaderiv(shaderID_, GL_COMPILE_STATUS, &success);
}

std::string Shader::getFile(std::string_view path) const {
    std::ifstream file(&path.front(), std::ios::binary | std::ios::ate);
    if (file) {
        uint64_t fileSize = file.tellg();
        file.seekg(std::ios::beg);
        std::string result(fileSize, 0);
        file.read(result.data(), fileSize);
        return result;
    }
    return {};
}

void Shader::use() const {
    glUseProgram(shaderID_);
}

void Shader::setBool(std::string_view name, bool value) const {
    glUniform1i(glGetUniformLocation(shaderID_, name.data()), (int) value);
}

void Shader::setInt(std::string_view name, int value) const {
    glUniform1i(glGetUniformLocation(shaderID_, name.data()), value);
}

void Shader::setFloat(std::string_view name, float value) const {
    glUniform1f(glGetUniformLocation(shaderID_, name.data()), value);
}

void Shader::setVec2(std::string_view name, const glm::vec2 &value) const {
    glUniform2fv(glGetUniformLocation(shaderID_, name.data()), 1, &value[0]);
}

void Shader::setVec2(std::string_view name, float x, float y) const {
    glUniform2f(glGetUniformLocation(shaderID_, name.data()), x, y);
}

void Shader::setVec3(std::string_view name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(shaderID_, name.data()), 1, &value[0]);
}

void Shader::setVec3(std::string_view name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(shaderID_, name.data()), x, y, z);
}

void Shader::setVec4(std::string_view name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(shaderID_, name.data()), 1, &value[0]);
}

void Shader::setVec4(std::string_view name, float x, float y, float z, float w) {
    glUniform4f(glGetUniformLocation(shaderID_, name.data()), x, y, z, w);
}

void Shader::setMat2(std::string_view name, const glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(shaderID_, name.data()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(std::string_view name, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(shaderID_, name.data()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(std::string_view name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(shaderID_, name.data()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setFloatArray(std::string_view name, const std::vector<float> &data) const {
    glUniform1fv(glGetUniformLocation(shaderID_, name.data()), data.size(), data.data());
}

