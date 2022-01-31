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
	Shader(const char* vertexFile, const char* fragmentFile); //Konstruktor który tworzy Shaderprogram z dwóch ró¿nych shaderów

	void Activate(); //Aktywacja ShaderProgram
	void Delete(); //Usuniecie ShaderProgram

private:
	// Gdy wyst¹pie b³¹d
	void compileErrors(unsigned int shader, const char* type);
};


#endif