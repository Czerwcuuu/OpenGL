#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID); // Generowanie VAO dla 1 obiektu


}

void VAO::LinkVBO(VBO VBO, GLuint layout)
{
	VBO.Bind();
	//Konfiguruj Vertex Attribute �eby OpenGL wiedzia� jak czyta� vBO
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	// W��cz Vertex Attribute �eby openGL wiedzia� jak go u�ywa�
	glEnableVertexAttribArray(layout);

	VBO.Unbind();
}

void VAO::Bind()
{
	glBindVertexArray(ID); //we� VAO jako obecny Vertex Array Object przypisuj�c go
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}