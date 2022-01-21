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

    glViewport(0, 0, 800, 800); //�adowanie frame'�w

        //TWORZENIE SHADER�W
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //Stw�rz shader verrt
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //Przypisz shader vert do Vertex Shader Object
    glCompileShader(vertexShader); //skompiluj shader vertex�w do kodu maszyny

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //Stw�rz shader frag
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // Przypisz shader frag do Fragment Shader Object
    glCompileShader(fragmentShader); //skompiluj shader fragment�w do kodu maszyny

    GLuint shaderProgram = glCreateProgram(); //wpakuj shadery do shaderProgramu

    glAttachShader(shaderProgram, vertexShader); //Przypisz shader vert do shaderprogam
    glAttachShader(shaderProgram, fragmentShader); //Przypisz shader frag do shaderprogam

    glLinkProgram(shaderProgram); //Przypisz shaderprogram do opengl

    glDeleteShader(vertexShader); //usuwamy shadery bo s� ju� przypisane do programu
    glDeleteShader(fragmentShader); //usuwamy shadery bo s� ju� przypisane do programu




    GLfloat vertices[] = // wierzcho�ki
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //Lewy g�rny r�g
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //Prawy dolny r�g
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, //G�rny r�g
        -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //�rodkowy lewy
        0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, //�rodkowy prawy
        0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // �rodkowy dolny
    };

    GLuint indices[] = //Indices - oszczedzanie pami�ci na sklonowane wierzcho�ki
    {
        0,3,5,
        3,2,4,
        5,4,1
    };

    //BUFFERY

    GLuint VAO,VBO,EBO; //Zmienna na buffery

    glGenVertexArrays(1, &VAO); // Generowanie VAO dla 1 obiektu
    glGenBuffers(1, &VBO); //Generuj VBO dla 1 obiektu
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO); //we� VAO jako obecny Vertex Array Object przypisuj�c go


    //Przypisz VBO jako GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //GL_ARRAY_BUFFER - u�ywany do vertex buffer�w
    //Wprowadz vertices do VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //rodzaj bufferu, rozmiar obiektu, vertices, rodzaj
    //rodzaj | GL_STREAM - b�dzie modyfikowany raz i u�ywany kilka razy
    //       | GL_DYNAMIC - b�dzie modyfikowany wiele raz i u�ywany wiele razy
    //       | GL_STATIC - b�dzie modyfikowany raz i u�ywany wiele razy

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Konfiguruj Vertex Attribute �eby OpenGL wiedzia� jak czyta� vBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // W��cz Vertex Attribute �eby openGL wiedzia� jak go u�ywa�
    glEnableVertexAttribArray(0); 

    //Przypisz VBO i VAO jako 0 �eby�my przypadkowo nie zmodyfikowali ich
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    //KOLORY T�A
    glClearColor(0.07f, 0.13f, 0.17f, 1.0);//Ustaw kolor (R,G,B,TRANS)
    glClear(GL_COLOR_BUFFER_BIT); //Zamien buffer i przypisz do niego nowy kolor
    glfwSwapBuffers(window); //Zamien tylni buffer z przednim


    // P�TLA G��WNA ------------------------------
    while (!glfwWindowShouldClose(window)) { //P�tla g��wna okna

        glClearColor(0.07f, 0.13f, 0.17f, 1.0);//Ustaw kolor (R,G,B,TRANS)
        glClear(GL_COLOR_BUFFER_BIT); //Zamien buffer i przypisz do niego nowy kolor
        glUseProgram(shaderProgram); //Powiedz OpenGL kt�rego ShaderProgramu u�ywa�
        glBindVertexArray(VAO); //Przypisz VAO �eby OpenGL go u�ywa�
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); //Narysuj tr�jk�t u�ywaj�c GL_TRIANGLE
        glfwSwapBuffers(window);



        glfwPollEvents(); //Zebranie puli event�w - bez tego nie b�dzie dzia�a�
    }
    // -------------------------------------------



    // USU� PO ZAKO�CZENIU --------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
}


