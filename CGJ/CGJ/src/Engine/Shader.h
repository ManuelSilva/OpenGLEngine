#ifndef __SHADER_H__
#define __SHADER_H__
#pragma once

#include "GL/glew.h"
#include <map>
#include <string>
#include <iostream>
#include <windows.h>


#define NUM_SHADER_TYPES 5

namespace Engine {
	enum ShaderType { VERTEX_SHADER, FRAGMENT_SHADER, GEOMETRY_SHADER, TESS_CONTROL, TESS_EVAL };
		
	class ShaderUniform {
		private:
			GLuint glHandle;
		public:
			inline GLuint getGLHandle() { return glHandle; }
			inline void setGLHandle(GLuint handle) { glHandle = handle; }
	};

	class VertexAttribute{
		private:
			GLuint glHandle;
		public:
			inline GLuint getGLHandle() { return glHandle; }
			inline void setGLHandle(GLuint handle) { glHandle = handle; }
	};

	class Shader {
		private:
			GLuint _program;
			int _numShaders;
			GLuint _shaders[5];
			std::map<std::string, VertexAttribute> _attribList;
			std::map<std::string, ShaderUniform> _unifLocationList;
		public:
			Shader();
			virtual ~Shader();

			void loadFromText(GLenum type, const char* cstr);
			void loadFromFile(GLenum type, const char* fileName);
			void loadFromPreCompiledText(GLenum type, const std::string& src) {}
			void loadFromPreCompiledFile(GLenum type, const char* fileName) {}
			void createAndLink();
			void setAttribute(const char* attrib);
			void setUniform(const char* uniform);

			GLuint getProgramID() const;
			VertexAttribute getAttribLocation(const char* attrib);
			ShaderUniform getUniformLocation(const char* unif);

			virtual void bind() const ;
			virtual void unBind() const;
			virtual void dispose();

		};

}
#endif