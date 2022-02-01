#ifndef EBO_CLASS_H
#define EBO_CLASS_H
#include<glad/glad.h>
#include<vector>

class EBO
{
public:
	GLuint ID; //ID EBO
	EBO(std::vector<GLuint>& indices); //Konstruktor EBO

	void Bind(); //Podpina EBO
	void Unbind(); //Odpina EBO
	void Delete(); //Usuwa EBO

};

#endif