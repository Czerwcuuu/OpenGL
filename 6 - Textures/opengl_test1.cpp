#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include<stb/stb_image.h>

#include"shaderClass.h"
#include"EBO.h"
#include"VBO.h"
#include"VAO.h"
#include"Texture.h"

GLfloat vertices[] = // wierzcho³ki
{
    //             KORDY  /    KOLORY           / TEXTURY
    -0.5f, -0.5f,0.0f,   1.0f, 0.0f, 0.0f,      0.0f,0.0f,//Lewy dolny róg
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.00f,     1.0f,0.0f,//Prawy dolny róg
    0.5f, 0.5f, 0.0f,    0.0f, 0.0f, 1.0f,      1.0f,1.0f,//Górny lewy róg
    -0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 1.0f,      0.0f,1.0f,//Górny prawy róg
};

GLuint indices[] = //Indices - oszczedzanie pamiêci na sklonowane wierzcho³ki
{
    0,1,2, //górny trójk¹t
    0,3,2, //dolny trójk¹t
};


int main()
{
    // KONFIGURACJA ------------------------------
    glfwInit(); //Inicjalizacja 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Wybór wersji major
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Wybór wersji minor
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Zestaw funkcji


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

    glViewport(0, 0, 800, 800); //£adowanie obrazu

    //SHADERY
    Shader shaderprogram("default.vert", "default.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8* sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3*sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    //Odbindowanie
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderprogram.ID, "scale");

    //Texture
    Texture cat("test.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    cat.texUnit(shaderprogram, "tex0", 0);

    // PÊTLA G£ÓWNA ------------------------------
    while (!glfwWindowShouldClose(window)) { //Pêtla g³ówna okna

        glClearColor(0.07f, 0.13f, 0.17f, 1.0);//Ustaw kolor (R,G,B,TRANS)
        glClear(GL_COLOR_BUFFER_BIT); //Zamien buffer i przypisz do niego nowy kolor
        shaderprogram.Activate(); //Powiedz OpenGL którego ShaderProgramu u¿ywaæ
        glUniform1f(uniID, 0.5f); // Scale uniform
        cat.Bind();//Zbinduj texture

        VAO1.Bind(); //Przypisz VAO ¿eby OpenGL go u¿ywa³
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //Narysuj trójk¹t u¿ywaj¹c GL_TRIANGLE
        glfwSwapBuffers(window);

        glfwPollEvents(); //Zebranie puli eventów - bez tego nie bêdzie dzia³aæ
    }


    // USUÑ PO ZAKOÑCZENIU --------------
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderprogram.Delete();
    cat.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
}
