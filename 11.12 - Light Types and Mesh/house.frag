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

vec4 pointLight()
{
	vec3 lightVec = lightPos - crntPos;
	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float inten = 1.0f / (a*dist*dist+b*dist+1.0f);

	//ambient lighting
	float ambient = 0.2f;

	//diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection),0.0f);

	//specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection),0.0f),8);
	float specular = specAmount * specularLight;

	return vec4(color, 1.0f) * lightColor * (diffuse + ambient + specular * inten);
}

vec4 spotLight()
{
	float outerCone = 0.9f;
	float innerCone = 0.95f;

	//ambient lighting
	float ambient = 0.2f;

	//diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);
	float diffuse = max(dot(normal, lightDirection),0.0f);

	//specular lighting
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection),0.0f),8);
	float specular = specAmount * specularLight;

	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone)/ (innerCone - outerCone), 0.0f, 1.0f);

	return vec4(color, 1.0f) * lightColor * (diffuse + ambient + specular * inten);
}


void main()
{

	FragColor = spotLight();
}