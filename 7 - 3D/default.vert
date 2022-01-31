#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

out vec3 color;
out vec2 texCoord;

uniform float scale;

//Input matryc potrzebnych dla widoku 3D z perspektyw¹
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
   // Przelicza pozycje wszystkich kordynatów danych vertexów 
   gl_Position = proj * view * model * vec4(aPos * scale, 1.0);
   color = aColor;
   texCoord = aTex;
}