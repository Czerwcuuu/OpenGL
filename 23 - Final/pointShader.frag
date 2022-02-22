#version 330 core

//Importuje obecn¹ pozycje z Vertex Shadera
in vec3 crntPos;
in vec3 Normal;
in vec3 color;
out vec4 FragColor;

//Pobiera color swiatla z glownej funkcji
uniform vec4 lightColor;
//Pobiera pozycje swiatla z glownej funkcji
uniform vec3 lightPos;
//Pobiera pozycje kamery z glownej funkcji
uniform vec3 camPos;

void main()
{
	//wynik
	FragColor = vec4(color, 1.0f) * lightColor;
}