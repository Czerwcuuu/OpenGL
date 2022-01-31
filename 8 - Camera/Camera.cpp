#include"Camera.h"

Camera::Camera(int width, int height, glm::vec3 position) {
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform) {
	//Inicjalizuje matryce, inaczej b�d� nullami
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);


	//Powoduje ze kamera patrzy sie we wlasciwym kierunku
	view = glm::lookAt(Position, Position + Orientation, Up);
	//Dodaje perspektywe do sceny
	projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);
	
	//Eksportuje kamere do vertex shadera
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::Inputs(GLFWwindow* window) {

	//Obs�uga klawiszy
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Position += speed * -glm::normalize(glm::cross(Orientation,Up));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		Position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		Position += speed * -Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		speed += 0.00001f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
		speed = 0.001f;
	}

	//Obs�uga myszy
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		//Ukrywa kursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		//Powoduje �e kamera nie skacze gdy klikamy
		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		//Przetrzymuje kordyynaty myszki
		double mouseX;
		double mouseY;
		//Przechwytuje kordyynaty myszki
		glfwGetCursorPos(window, &mouseX, &mouseY);

		//Normalizuje kordynaty tak �eby zaczyna�y si� na �rodku ekranu
		// wtedy transformuje je na stopnie(degrees)
		float rotx = sensitivity * (float)(mouseY - (height / 2)) / height;
		float roty = sensitivity * (float)(mouseX - (height / 2)) / height;

		//Kalkuluje nadchodz�c� zmiane wertykaln� w Orientation
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotx), glm::normalize(glm::cross(Orientation, Up)));

		//Decyzja czy zmiana jest dozwolona czy te� nie
		if (!((glm::angle(newOrientation, Up) <= glm::radians(5.0f)) or (glm::angle(newOrientation, -Up) <= glm::radians(5.0f)))) {
			Orientation = newOrientation;
		}

		//Obraca w prawo i lewo
		Orientation = glm::rotate(Orientation, glm::radians(-roty), Up);

		//Ustawia kursor na �rodku ekranu
		glfwSetCursorPos(window, (width / 2), (height / 2));

	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		//Przywraca kursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		//Powoduje �e jest pewno�� �e kamera nie b�dzie skaka�a przy kolejnym obracaniu
		firstClick = true;
	}
}