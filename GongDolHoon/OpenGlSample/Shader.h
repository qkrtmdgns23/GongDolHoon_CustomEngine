#ifndef SHADER_H
#define SHADER_H

#include <string>

// library
#include "include/GL/glew.h"	
#include "glm/glm.hpp"

class Shader
{
public:
	Shader(const char* vertex_shader_path, const char* fragment_shader_path);
	~Shader();

	// use or unuse shader
	void use();
	void un_use();

	// utilty uniform funcs
	void set_bool(const std::string& name, bool value);
	void set_int(const std::string& name, int value);
	void set_float(const std::string& name, float value);
	void set_vec2(const std::string& name, const glm::vec2& value);
	void set_vec2(const std::string& name, float x, float y);
	void set_vec3(const std::string& name, const glm::vec3& value);
	void set_vec3(const std::string& name, float x, float y, float z);
	void set_vec4(const std::string& name, const glm::vec4& value);
	void set_vec4(const std::string& name, float x, float y, float z, float w);
	void set_mat2(const std::string& name, const glm::mat2& mat);
	void set_mat3(const std::string& name, const glm::mat3& mat);
	void set_mat4(const std::string& name, const glm::mat4& mat);

	// Property
	GLuint get_program_id() const;
	

private:
	GLuint program_id_;

};

#endif /* SHADER_H */