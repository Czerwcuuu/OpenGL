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


const unsigned int width = 800;
const unsigned int height = 800;

GLfloat vertices[] = // wierzcho³ki
{
    //             KORDY  /    KOLORY           / TEXTURY
    -0.5f, 0.0f,0.5f,      0.83f, 0.70f, 0.44f,      0.0f,0.0f,
    -0.5f, 0.0f, -0.5f,    0.83f, 0.70f, 0.44f,     5.0f,0.0f,
     0.5f, 0.0f, -0.5f,    0.83f, 0.70f, 0.44f,      0.0f,0.0f,
     0.5f, 0.0f, 0.5f,     0.83f, 0.70f, 0.44f,      5.0f,0.0f,
     0.0f, 0.8f, 0.0f,     0.92f, 0.86f, 0.78f,   2.5f, 5.0f
};

GLuint indices[] = //Indices - oszczedzanie pamiêci na sklonowane wierzcho³ki
{
    0,1,2, 
    0,2,3,
    0,1,4,
    1,2,4,
    2,3,4,
    3,0,4

};


int main()
{
    // KONFIGURACJA ------------------------------
    glfwInit(); //Inicjalizacja 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Wybór wersji major
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Wybór wersji minor
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Zestaw funkcji


    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL); //szerokoœæ, wysokoœæ, nazwa, fullscreen, nw
    if (window == NULL) //Sprawdzanie czy z oknem wszystko ok
    {
        std::cout << "Blad podczas ladowania okna" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); //Wybor okna na ktorym dziala opengl

    gladLoadGL(); //£adowanie glada
    // -------------------------------------------

    glViewport(0, 0, width, height); //£adowanie obrazu

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
    Texture cat("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    cat.texUnit(shaderprogram, "tex0", 0);

    float rotation = 0.0f;
    double prevTime = glfwGetTime();

    //W³¹cza buffer 'glebokosci'
    glEnable(GL_DEPTH_TEST);

    // PÊTLA G£ÓWNA ------------------------------
    while (!glfwWindowShouldClose(window)) { //Pêtla g³ówna okna

        glClearColor(0.07f, 0.13f, 0.17f, 1.0);//Ustaw kolor (R,G,B,TRANS)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Zamien buffer warstwy dolnej i glebokosci
        shaderprogram.Activate(); //Powiedz OpenGL którego ShaderProgramu u¿ywaæ

        //Timer
        double crntTime = glfwGetTime();
        if (crntTime - prevTime >= 1 / 60) {
            rotation += 0.01f;
            prevTime = crntTime;
        }

        //Inicjalizacja matryc ¿eby nie by³y puste
        glm::mat4 model = glm::mat4(1.0f); //Inicjalizacja
        glm::mat4 view = glm::mat4(1.0f); //Inicjalizacja
        glm::mat4 proj = glm::mat4(1.0f); //Inicjalizacja

        //Przypisanie ró¿nych transformacji do ka¿dych matryc
        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        proj = glm::perspective(glm::radians(45.0f), (float)(width / height), 0.1f, 100.0f);
        model = glm::rotate(model, glm::radians(rotation),glm::vec3(0.0f,1.0f,0.0f));

        //Przekazanie do vertexshadera
        int modelLoc = glGetUniformLocation(shaderprogram.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(shaderprogram.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projLoc = glGetUniformLocation(shaderprogram.ID, "proj");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));


        glUniform1f(uniID, 0.5f); // Scale uniform
        cat.Bind();//Zbinduj texture

        VAO1.Bind(); //Przypisz VAO ¿eby OpenGL go u¿ywa³
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0); //Narysuj trójk¹t u¿ywaj¹c GL_TRIANGLE
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
