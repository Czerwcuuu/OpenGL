#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	GLuint ID; //ID VAO
	VAO(); //Konstruktor który generuje ID VAO

	void LinkVBO(VBO VBO, GLuint layout); // Pod³¹cza VBO do VAO u¿ywaj¹c wybranego layouta
	void Bind(); //Podpina VAO
	void Unbind(); //Odpina VAO
	void Delete(); //Usuwa VAO
};

#endif
