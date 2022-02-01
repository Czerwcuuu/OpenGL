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
#include"Camera.h"


const unsigned int width = 800;
const unsigned int height = 800;

GLfloat vertices[] = // wierzcho³ki
{
    //             KORDY  /    KOLORY                / TEXTURY      /   NORMALS
    -1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
    -1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
     1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
     1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
};

GLuint indices[] = //Indices - oszczedzanie pamiêci na sklonowane wierzcho³ki
{
    0, 1, 2, // Dolna scianka
    0, 2, 3, // Dolna scianka
};

GLfloat lightVertices[] =
{ //  KORDY
    -0.1f, -0.1f, 0.1f,
    -0.1f, -0.1f, -0.1f,
    0.1f, -0.1f, -0.1f,
    0.1f, -0.1f, 0.1f,

    -0.1f, 0.1f, 0.1f,
    -0.1f, 0.1f, -0.1f,
    0.1f, 0.1f, -0.1f,
    0.1f, 0.1f, 0.1f,
};

GLuint lightIndices[] = 
{
    0,1,2,
    0,3,2,//
    0,4,7,
    0,7,3,//
    3,7,6,
    3,6,2,//
    2,6,5,
    2,1,5,//
    1,5,4,
    1,0,4,//
    4,7,6,
    4,5,6,//
};

GLfloat houseVertices[] =
{
    -1.0f,0.0f,1.0f,     0.9f, 0.9f, 0.8f,       0.0f, 1.0f, 0.0f,
    1.0f, 0.0f,1.0f,    0.9f, 0.9f, 0.8f,        0.0f, 1.0f, 0.0f,
    1.0f, 0.0f,-1.0f,    0.9f, 0.9f, 0.8f,       0.0f, 1.0f, 0.0f,
    -1.0f,0.0f, -1.0f,    0.9f, 0.9f, 0.8f,       0.0f, 1.0f, 0.0f,

    1.0f, 0.0f, -1.0f,   0.83f, 0.70f, 0.44f,       0.0f, 1.0f, 0.0f,
    -1.0f, 0.0f, -1.0f,    0.83f, 0.70f, 0.44f,     0.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, -1.0f,    0.83f, 0.70f, 0.44f,     0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, -1.0f,   0.83f, 0.70f, 0.44f,      0.0f, 1.0f, 0.0f,

    -1.0f, 0.0f, 1.0f,    0.83f, 0.70f, 0.44f,       0.0f, 1.0f, 0.0f,
    -1.0f, 0.0f, -1.0f,    0.83f, 0.70f, 0.44f,      0.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, -1.0f,    0.83f, 0.70f, 0.44f,      0.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 1.0f,    0.83f, 0.70f, 0.44f,       0.0f, 1.0f, 0.0f,

    1.0f, 0.0f, 1.0f,    0.83f, 0.70f, 0.44f,       0.0f, 1.0f, 0.0f,
    1.0f, 0.0f,-1.0f,    0.83f, 0.70f, 0.44f,      0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, -1.0f,    0.83f, 0.70f, 0.44f,       0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f,    0.83f, 0.70f, 0.44f,       0.0f, 1.0f, 0.0f,

    -1.0f, 0.0f, 1.0f,    0.83f, 0.70f, 0.44f,        0.0f, 1.0f, 0.0f, //Scianka drzwi lewo
    -0.2f, 0.0f, 1.0f,    0.83f, 0.70f, 0.44f,        0.0f, 1.0f, 0.0f,
    -0.2f, 1.0f, 1.0f,    0.83f, 0.70f, 0.44f,        0.0f, 1.0f, 0.0f,
    -1.0f, 1.0f, 1.0f,    0.83f, 0.70f, 0.44f,       0.0f, 1.0f, 0.0f,

    -0.2f, 1.0f, 1.0f,    0.83f, 0.70f, 0.44f,        0.0f, 1.0f, 0.0f, //Scianka drzwi srodek
    -0.2f, 0.6f, 1.0f,    0.83f, 0.70f, 0.44f,        0.0f, 1.0f, 0.0f,
    0.2f,  0.6f, 1.0f,    0.83f, 0.70f, 0.44f,        0.0f, 1.0f, 0.0f,
    0.2f, 1.0f, 1.0f,     0.83f, 0.70f, 0.44f,        0.0f, 1.0f, 0.0f,

    0.2f, 1.0f, 1.0f,     0.83f, 0.70f, 0.44f,        0.0f, 1.0f, 0.0f, //Scianka drzwi prawo
    0.2f, 0.0f, 1.0f,    0.83f, 0.70f, 0.44f,        0.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 1.0f,    0.83f, 0.70f, 0.44f,       0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f,    0.83f, 0.70f, 0.44f,        0.0f, 1.0f, 0.0f,

};

GLuint houseIndices[] =
{
    0,1,2, // Dolna scianka
    0,3,2,
    4,5,6, // Tylnia scianka
    4,7,6,
    8,9,10, // Lewa scianka
    8,11,10,
    12,13,14, // Prawa scianka
    12,15,14,
    16,17,18, //Lewo ramka drzwi
    16,19,18,
    20,21,22, //Srodek ramka drzwi
    20,23,22,
    24,25,26, //Prawo ramka drzwi
    24,27,26
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
    Shader shaderProgram("default.vert", "default.frag");

    //Generuje VAO i przypisuje go
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices)); // Generuje VBO
    EBO EBO1(indices, sizeof(indices)); // Generuje EBO

    //Przypisuje VBO takie jak kordyynaty czy kolory do VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11* sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3*sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

    //Odbindowanie
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();


    //Kwadrat obs³uguj¹cy œwiat³o
    Shader lightShader("light.vert", "light.frag");

    //Generuje VAO i przypisuje
    VAO lightVAO;
    lightVAO.Bind();

    //Generuje VBO i przypisuje do vertexow
    VBO lightVBO(lightVertices, sizeof(lightVertices));
    //Generuje EBO i rzypisuje do indices
    EBO lightEBO(lightIndices, sizeof(lightIndices));

    //Przypisuje atrybuty VBO takie jak kordyynaty czy kolory
    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    
    //Unbinduje zebysmy przypadkowo ich nie zmodyfikowali
    lightVAO.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind(); 

    Shader houseShader("house.vert", "house.frag");

    VAO houseVAO;
    houseVAO.Bind();

    VBO houseVBO(houseVertices, sizeof(houseVertices));
    EBO houseEBO(houseIndices, sizeof(houseIndices));

    houseVAO.LinkAttrib(houseVBO, 0, 3, GL_FLOAT, 9 * sizeof(float), (void*)0);
    houseVAO.LinkAttrib(houseVBO, 1, 3, GL_FLOAT, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    houseVAO.LinkAttrib(houseVBO, 2, 3, GL_FLOAT, 9 * sizeof(float), (void*)(6 * sizeof(float)));

    houseVAO.Unbind();
    houseVBO.Unbind();
    houseEBO.Unbind();

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);

    glm::vec3 housePos = glm::vec3(3.0f, 0.0f, 3.0f);
    glm::mat4 houseModel = glm::mat4(1.0f);
    houseModel = glm::translate(houseModel, housePos);

    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    houseShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(houseShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(houseModel));
    glUniform4f(glGetUniformLocation(houseShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(houseShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);



    //Texture
    Texture planksTex("planks.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    planksTex.texUnit(shaderProgram, "tex0", 0);
    Texture planksSpec("planksSpec.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
    planksSpec.texUnit(shaderProgram, "tex1", 1);

    //W³¹cza buffer 'glebokosci'
    glEnable(GL_DEPTH_TEST);

    //Tworzy obiekt kamery
    Camera camera(width,height,glm::vec3(0.0f,0.0f,2.0f));

    // PÊTLA G£ÓWNA ------------------------------
    while (!glfwWindowShouldClose(window)) { //Pêtla g³ówna okna

        glClearColor(0.07f, 0.13f, 0.17f, 1.0);//Ustaw kolor (R,G,B,TRANS)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Zamien buffer warstwy dolnej i glebokosci
        
        //Obs³uga klawiszów kamery
        camera.Inputs(window);
        //Aktualizuje i eksportuje martix kamery do VertexShadera
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        shaderProgram.Activate();
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
        camera.Matrix(shaderProgram, "camMatrix");

        planksTex.Bind();//Zbinduj texture
        planksSpec.Bind();

        VAO1.Bind(); //Przypisz VAO ¿eby OpenGL go u¿ywa³
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0); //Narysuj trójk¹t u¿ywaj¹c GL_TRIANGLE

        houseShader.Activate();
        camera.Matrix(houseShader, "camMatrix");
        houseVAO.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(houseIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

        lightShader.Activate();
        camera.Matrix(lightShader, "camMatrix");
        lightVAO.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);




        glfwSwapBuffers(window);

        glfwPollEvents(); //Zebranie puli eventów - bez tego nie bêdzie dzia³aæ
    }


    // USUÑ PO ZAKOÑCZENIU --------------
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
    planksTex.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
}
