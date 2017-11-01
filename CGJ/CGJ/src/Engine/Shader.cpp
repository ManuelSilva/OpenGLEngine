#include "Shader.h"
#include "fstream"

Engine::Shader::Shader():_program(0), _numShaders(0)
{
	_shaders[VERTEX_SHADER] = 0;
	_shaders[FRAGMENT_SHADER] = 0;
	_shaders[GEOMETRY_SHADER] = 0;
	_shaders[TESS_CONTROL] = 0;
	_shaders[TESS_EVAL] = 0;
	_attribList.clear();
	_unifLocationList.clear();
}

Engine::Shader::~Shader() {}

void Engine::Shader::loadFromText(GLenum type, const char* cstr) {
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &cstr, nullptr);
	glCompileShader(shader);
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogSize;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogSize);
		GLchar *infoLog = new GLchar[infoLogSize];
		glGetShaderInfoLog(shader, infoLogSize, nullptr, infoLog);
		std::cout << infoLog << std::endl;
		delete[] infoLog;
	}
	_shaders[_numShaders++] = shader;
}

void Engine::Shader::createAndLink() {
	_program = glCreateProgram();
	if (_shaders[VERTEX_SHADER] != 0)
		glAttachShader(_program, _shaders[VERTEX_SHADER]);
	if (_shaders[FRAGMENT_SHADER] != 0)	
		glAttachShader(_program, _shaders[FRAGMENT_SHADER]);
	if (_shaders[GEOMETRY_SHADER] != 0)
		glAttachShader(_program, _shaders[GEOMETRY_SHADER]);
	if (_shaders[TESS_CONTROL] != 0)
		glAttachShader(_program, _shaders[TESS_CONTROL]);
	if (_shaders[TESS_EVAL] != 0)
		glAttachShader(_program, _shaders[TESS_EVAL]);

	GLint status;
	glLinkProgram(_program);
	glGetProgramiv(_program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogSize;
		glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &infoLogSize);
		GLchar *infoLog = new GLchar[infoLogSize];
		glGetProgramInfoLog(_program, infoLogSize, nullptr, infoLog);
		delete[] infoLog;
	}

/*
	glDetachShader(_program, _shaders[VERTEX_SHADER]);
	glDetachShader(_program, _shaders[FRAGMENT_SHADER]);
	glDetachShader(_program, _shaders[GEOMETRY_SHADER]);
	glDetachShader(_program, _shaders[TESS_CONTROL]);
	glDetachShader(_program, _shaders[TESS_EVAL]);


	glDeleteShader(_shaders[VERTEX_SHADER]);
	glDeleteShader(_shaders[FRAGMENT_SHADER]);
	glDeleteShader(_shaders[GEOMETRY_SHADER]);
	glDeleteShader(_shaders[TESS_CONTROL]);
	glDeleteShader(_shaders[TESS_EVAL]);
*/

}

void Engine::Shader::bind() const {
	glUseProgram(_program);
}

void Engine::Shader::unBind() const {
	glUseProgram(0);
}

void Engine::Shader::setAttribute(const char* attrib) {
	_attribList[attrib].setGLHandle(glGetAttribLocation(_program, attrib));
}

void Engine::Shader::setUniform(const char* unif) {
	_unifLocationList[unif].setGLHandle(glGetUniformLocation(_program, unif));
}

Engine::VertexAttribute Engine::Shader::getAttribLocation(const char* attrib) {
	return _attribList[attrib];
}

Engine::ShaderUniform Engine::Shader::getUniformLocation(const char* unif) {
	return _unifLocationList[unif];
}

GLuint Engine::Shader::getProgramID() const { return _program; }

void Engine::Shader::loadFromFile(GLenum which, const char* fileName) {
	std::ifstream fparser;
	fparser.open(fileName, std::ios_base::in);
	if (fparser) {
		std::string buffer(std::istreambuf_iterator<char>(fparser), (std::istreambuf_iterator<char>()));
		loadFromText(which, buffer.c_str());
	}
	else {
		std::cout << "Invalid fileNamePath" << std::endl;
	}
}

void Engine::Shader::dispose() {
	glDeleteProgram(_program);
	_program = -1;
}