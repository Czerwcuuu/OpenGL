#include"shaderClass.h"

// Wczytywanie z plik�w tekstowych
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

// Konstruktor budowany z dw�ch r�nych plik�w shader�w
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Czyta fertexfile i fragmentfile
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	//arraysKonwertuje pliki shader�w
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //Stw�rz shader verrt
	glShaderSource(vertexShader, 1, &vertexSource, NULL); //Przypisz shader vert do Vertex Shader Object
	glCompileShader(vertexShader); //skompiluj shader vertex�w do kodu maszyny
	compileErrors(vertexShader, "VERTEX"); //sprawdza czy wszystko skompilowane OK

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //Stw�rz shader frag
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL); // Przypisz shader frag do Fragment Shader Object
	glCompileShader(fragmentShader); //skompiluj shader fragment�w do kodu maszyny
	compileErrors(fragmentShader, "FRAGMENT"); //sprawdza czy wszystko skompilowane OK

	
	ID = glCreateProgram(); //wpakuj shadery do shaderProgramu

	glAttachShader(ID, vertexShader); //Przypisz shader vert do shaderprogam
	glAttachShader(ID, fragmentShader); //Przypisz shader frag do shaderprogam

	glLinkProgram(ID); //Przypisz shaderprogram do opengl
	compileErrors(ID, "PROGRAM");

	glDeleteShader(vertexShader); //usuwamy shadery bo s� ju� przypisane do programu
	glDeleteShader(fragmentShader); //usuwamy shadery bo s� ju� przypisane do programu

}

// Aktywuje program Shader�w
void Shader::Activate()
{
	glUseProgram(ID);
}

// Usuwa program Shader�w
void Shader::Delete()
{
	glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}