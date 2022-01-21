#include"Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
    //Przypisz teksture do tekstury obiektu
	type = texType;

    //Przetrzymuje szerokosc, wysokosc i liczbe kolorow zdjecia
    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true); //Obraca zdjecie
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0); //Czyta zdjecie z pliku i przetrzymuje w bajtach

    glGenTextures(1, &ID); //Generuje obiekt tekstury
    glActiveTexture(slot); //Przypisz teksture do jednostki Tekstury
    glBindTexture(texType, ID);

    //PARAMETRY
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // GL_NEAREST - tak jak jest
    // GL_LINEAR - uzupe�nia brakuj�ce piksele, co czasami daje efekt blura
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //Gdyby�my chcieli obramowanie textury
    // float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor)
    glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
    // Generowanie MipMapy
    glGenerateMipmap(texType);

    //Odczepienie textury
    stbi_image_free(bytes);

    //Odbinduj teksture �eby przypadkowo nie zmodyfikowa�
    glBindTexture(texType, 0);


}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
    GLuint tex0Uni = glGetUniformLocation(shader.ID, uniform); //Lokacja uniformu
    shader.Activate(); //Shader musi by� aktywowany przed zmian� warto�ci uniformu
    glUniform1f(tex0Uni, unit); //Ustawia warto�� uniformu
}

void Texture::Bind()
{
    glBindTexture(type, ID);
}

void Texture::Unbind()
{
    glBindTexture(type, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}