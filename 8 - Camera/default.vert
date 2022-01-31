#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

out vec3 color;
out vec2 texCoord;

//Importuje matrix kamery z g��wnej funkcji
uniform mat4 camMatrix;

void main()
{
   // Przelicza pozycje wszystkich kordynat�w danych vertex�w 
   gl_Position = camMatrix * vec4(aPos, 1.0);
   color = aColor;
   texCoord = aTex;
}