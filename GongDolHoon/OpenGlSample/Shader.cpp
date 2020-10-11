// custom header
#include "Shader.h"
#include "FileManager.h"

Shader::Shader(const char* vertex_shader_path, const char* fragment_shader_path)
{
	program_id_ = FileManager::get_instance()->load_shaders(vertex_shader_path, fragment_shader_path);

}

Shader::~Shader()
{
	glDeleteProgram(this->program_id_);
}

void Shader::use()
{
	glUseProgram(program_id_);
}

void Shader::un_use()
{
	glUseProgram(0);
}

void Shader::set_bool(const std::string& name, bool value)
{
	use();
	glUniform1i(glGetUniformLocation(program_id_, name.c_str()), (int)value);
	un_use();
}
// ------------------------------------------------------------------------
void Shader::set_int(const std::string& name, int value)
{
	use();
	glUniform1i(glGetUniformLocation(program_id_, name.c_str()), value);
	un_use();
}
// ------------------------------------------------------------------------
void Shader::set_float(const std::string& name, float value)
{
	use();
	glUniform1f(glGetUniformLocation(program_id_, name.c_str()), value);
	un_use();
}
// ------------------------------------------------------------------------
void Shader::set_vec2(const std::string& name, const glm::vec2& value)
{
	use();
	glUniform2fv(glGetUniformLocation(program_id_, name.c_str()), 1, &value[0]);
	un_use();
}
void Shader::set_vec2(const std::string& name, float x, float y)
{
	use();
	glUniform2f(glGetUniformLocation(program_id_, name.c_str()), x, y);
	un_use();
}
// ------------------------------------------------------------------------
void Shader::set_vec3(const std::string& name, const glm::vec3& value)
{
	use();
	glUniform3fv(glGetUniformLocation(program_id_, name.c_str()), 1, &value[0]);
	un_use();
}
void Shader::set_vec3(const std::string& name, float x, float y, float z)
{
	use();
	glUniform3f(glGetUniformLocation(program_id_, name.c_str()), x, y, z);
	un_use();
}
// ------------------------------------------------------------------------
void Shader::set_vec4(const std::string& name, const glm::vec4& value)
{
	use();
	glUniform4fv(glGetUniformLocation(program_id_, name.c_str()), 1, &value[0]);
	un_use();
}
void Shader::set_vec4(const std::string& name, float x, float y, float z, float w)
{
	use();
	glUniform4f(glGetUniformLocation(program_id_, name.c_str()), x, y, z, w);
	un_use();
}
// ------------------------------------------------------------------------
void Shader::set_mat2(const std::string& name, const glm::mat2& mat)
{
	use();
	glUniformMatrix2fv(glGetUniformLocation(program_id_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	un_use();
}
// ------------------------------------------------------------------------
void Shader::set_mat3(const std::string& name, const glm::mat3& mat)
{
	use();
	glUniformMatrix3fv(glGetUniformLocation(program_id_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	un_use();
}
// ------------------------------------------------------------------------
void Shader::set_mat4(const std::string& name, const glm::mat4& mat)
{
	use();
	glUniformMatrix4fv(glGetUniformLocation(program_id_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	un_use();
}

GLuint Shader::get_program_id() const
{
	return program_id_;
}