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

//Vertex Shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment Shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


int main()
{
    // KONFIGURACJA ------------------------------
    glfwInit(); //Inicjalizacja 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Wybór wersji major
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Wybór wersji minor
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Zestaw funkcji


    GLfloat vertices[] =
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
    };


    GLFWwindow* window = glfwCreateWindow(800, 800, "LearnOpenGL", NULL, NULL); //szerokoœæ, wysokoœæ, nazwa, fullscreen, nw
    if (window == NULL) //Sprawdzanie czy z oknem wszystko ok
    {
        std::cout << "Blad podczas ladowania okna" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); //Wybor okna na ktorym dziala opengl

    gladLoadGL(); //£adowanie glada
    // -------------------------------------------






    // PÊTLA G£ÓWNA ------------------------------
    glViewport(0, 0, 800, 800); //£adowanie frame'ów

        //TWORZENIE SHADERÓW
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //Stwórz shader verrt
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //Przypisz shader vert
    glCompileShader(vertexShader); //skompiluj shader vertexów

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //Stwórz shader frag
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // Przypisz shader frag
    glCompileShader(fragmentShader); //skompiluj shader fragmentów

    GLuint shaderProgram = glCreateProgram(); //wpakuj shadery do shaderProgramu

    glAttachShader(shaderProgram, vertexShader); //Przypisz shader vert do shaderprogam
    glAttachShader(shaderProgram, fragmentShader); //Przypisz shader frag do shaderprogam

    glLinkProgram(shaderProgram); //Przypisz shaderprogram do opengl

    glDeleteShader(vertexShader); //usuwamy shadery bo s¹ ju¿ przypisane do programu
    glDeleteShader(fragmentShader); //usuwamy shadery bo s¹ ju¿ przypisane do programu


    //BUFFERY

    GLuint VAO,VBO; //Zmienna na buffery

    glGenVertexArrays(1, &VAO); // generowanie VAO
    glGenBuffers(1, &VBO); //Generuj buffer

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO); //GL_ARRAY_BUFFER - u¿ywany do vertex bufferów
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //rodzaj bufferu, rozmiar obiektu, vertices, rodzaj
    //rodzaj | GL_STREAM - bêdzie modyfikowany raz i u¿ywany kilka razy
    //       | GL_DYNAMIC - bêdzie modyfikowany wiele raz i u¿ywany wiele razy
    //       | GL_STATIC - bêdzie modyfikowany raz i u¿ywany wiele razy

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    //KOLORY T£A
    glClearColor(0.07f, 0.13f, 0.17f, 1.0);//Ustaw kolor (R,G,B,TRANS)
    glClear(GL_COLOR_BUFFER_BIT); //Zamien buffer i przypisz do niego nowy kolor
    glfwSwapBuffers(window); //Zamien tylni buffer z przednim

    while (!glfwWindowShouldClose(window)) { //Pêtla g³ówna okna

        glClearColor(0.07f, 0.13f, 0.17f, 1.0);//Ustaw kolor (R,G,B,TRANS)
        glClear(GL_COLOR_BUFFER_BIT); //Zamien buffer i przypisz do niego nowy kolor
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);



        glfwPollEvents(); //Zebranie puli eventów - bez tego nie bêdzie dzia³aæ
    }
    // -------------------------------------------



    // USUÑ PO ZAKOÑCZENIU --------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
}


