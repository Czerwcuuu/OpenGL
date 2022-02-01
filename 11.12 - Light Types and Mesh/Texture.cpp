#include"Texture.h"

Texture::Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType)
{
    //Przypisz teksture do tekstury obiektu
	type = texType;

    //Przetrzymuje szerokosc, wysokosc i liczbe kolorow zdjecia
    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true); //Obraca zdjecie
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0); //Czyta zdjecie z pliku i przetrzymuje w bajtach

    glGenTextures(1, &ID); //Generuje obiekt tekstury
    glActiveTexture(GL_TEXTURE0 + slot); //Przypisz teksture do jednostki Tekstury
    unit = slot;
    glBindTexture(GL_TEXTURE_2D, ID);

    //PARAMETRY
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // GL_NEAREST - tak jak jest
    // GL_LINEAR - uzupe³nia brakuj¹ce piksele, co czasami daje efekt blura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //Gdybyœmy chcieli obramowanie textury
    // float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
    // Generowanie MipMapy
    glGenerateMipmap(GL_TEXTURE_2D);

    //Odczepienie textury
    stbi_image_free(bytes);

    //Odbinduj teksture ¿eby przypadkowo nie zmodyfikowaæ
    glBindTexture(GL_TEXTURE_2D, 0);


}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
    GLuint texUni = glGetUniformLocation(shader.ID, uniform); //Lokacja uniformu
    shader.Activate(); //Shader musi byæ aktywowany przed zmian¹ wartoœci uniformu
    glUniform1f(texUni, unit); //Ustawia wartoœæ uniformu
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}