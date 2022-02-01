#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H
#define GLM_ENABLE_EXPERIMENTAL

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

class Camera
{
public:
	//Przetrzymuje g³ówne vectory kamery
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	//Powoduje ze kamera nie skacze podczas klikania
	bool firstClick = true;

	//Przetrzymuje szerokosc i wysokosc okna
	int width, height;

	//Poprawia szybkoœæ i czu³oœæ podczas obracania
	float speed = 0.001f;
	float sensitivity = 100.0f;

	//Konstruktor Camery
	Camera(int width, int height, glm::vec3 position);

	//Aktualizuje i eksportuje matrix kamery do Vertex Shadera
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	void Matrix(Shader& shader, const char* uniform);
	//Obs³uga klawiszów
	void Inputs(GLFWwindow* window);
};


#endif
