#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <sys/stat.h>
#include <filesystem>
#include <unistd.h>
using namespace std;
namespace fs = std::filesystem;

class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(const char *vertexPath, const char *fragmentPath)
    {
        // 1. 파일 경로에서 vertex/fragment source code를 가져옴
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // ifstream 객체가 exception을 던지는지 확인
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        const char *dir = vertexPath;

        // Structure which would store the metadata
        struct stat sb;
        if (stat(dir, &sb) == 0)
            cout << dir << "The path is valid!" << std::endl;
        else
            cout << dir << "The Path is invalid!" << std::endl;

        // std::cout << "Current path is " << fs::current_path() << std::endl;
        char tmp[256];
        getcwd(tmp, 256);
        cout << "Current working directory: " << tmp << endl;

        std::cout << vertexPath << std::endl;
        try
        {
            // 파일 열기
            vShaderFile.open(vertexPath);
            std::cout << vertexPath << std::endl;

            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // file buffer를 stream에 넣기
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // file handlers 닫기
            vShaderFile.close();
            fShaderFile.close();
            // stream을 string으로 변환
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (const std::ifstream::failure &e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }
        const char *vShaderCode = vertexCode.c_str();
        const char *fShaderCode = fragmentCode.c_str();

        // 2. shaders를 컴파일
        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        // vertex Shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        // 컴파일 에러가 있는지 print
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
        };

        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        // 컴파일 에러가 있는지 print
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
        };

        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        // 컴파일 에러 확인
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                      << infoLog << std::endl;
        };

        // shaders는 프로그램에 연결되어 더이상 필요하지 않으므로 삭제
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    };
    // use/activate the shader
    void use()
    {
        glUseProgram(ID);
    };
    // utility uniform functions
    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    };
    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    };
    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    };
};

#endif