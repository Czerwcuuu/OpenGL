#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <iostream>



int main()
{
    // KONFIGURACJA ------------------------------
    glfwInit(); //Inicjalizacja 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Wyb�r wersji major
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Wyb�r wersji minor
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Zestaw funkcji

    
    GLFWwindow* window = glfwCreateWindow(800, 800, "LearnOpenGL", NULL, NULL); //szeroko��, wysoko��, nazwa, fullscreen, nw
    if (window == NULL) //Sprawdzanie czy z oknem wszystko ok
    {
        std::cout << "Blad podczas ladowania okna" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); //Wybor okna na ktorym dziala opengl

    gladLoadGL(); //�adowanie glada
    // -------------------------------------------


    // P�TLA G��WNA ------------------------------
    glViewport(0, 0, 800, 800); //�adowanie frame'�w

    glClearColor(0.07f, 0.13f, 0.17f, 1.0);//Ustaw kolor (R,G,B,TRANS)
    glClear(GL_COLOR_BUFFER_BIT); //Zamien buffer i przypisz do niego nowy kolor
    glfwSwapBuffers(window); //Zamien tylni buffer z przednim

    while (!glfwWindowShouldClose(window)) { //P�tla g��wna okna
        
        glfwPollEvents(); //Zebranie puli event�w - bez tego nie b�dzie dzia�a�
    }
    // -------------------------------------------
    


    // USU� PO ZAKO�CZENIU --------------
    glfwDestroyWindow(window);
    glfwTerminate();
}


