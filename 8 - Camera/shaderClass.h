#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	GLuint ID; //ID ShaderProgramu
	Shader(const char* vertexFile, const char* fragmentFile); //Konstruktor kt�ry tworzy Shaderprogram z dw�ch r�nych shader�w

	void Activate(); //Aktywacja ShaderProgram
	void Delete(); //Usuniecie ShaderProgram

private:
	// Gdy wyst�pie b��d
	void compileErrors(unsigned int shader, const char* type);
};


#endif