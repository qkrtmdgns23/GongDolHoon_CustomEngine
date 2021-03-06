#include "shader.h"
#include "file_manager.h"

namespace gdh_engine {
	namespace object {
		Shader::Shader(const char* vertex_path, const char* fragment_path)
		{
			shader_program_identity_ = gdh_engine::manager::file::FileManager::get_instance()->
				LoadAndCreateShader(vertex_path, fragment_path);
		}
		Shader::Shader(std::string vertex_path, std::string fragment_path)
		{
			shader_program_identity_ = gdh_engine::manager::file::FileManager::get_instance()->
				LoadAndCreateShader(vertex_path, fragment_path);
		}
		Shader::~Shader()
		{
			glDeleteShader(this->shader_program_identity_);
		}

		void Shader::UseShader()
		{
			glUseProgram(shader_program_identity_);
		}
		void Shader::UnuseShader()
		{
			glUseProgram(0);
		}

		void Shader::SetBooleanDataTypeUniformVariable(const std::string& name, bool value) const
		{
			glUniform1i(glGetUniformLocation(shader_program_identity_, name.c_str()), (int)value);
		}
		void Shader::SetBooleanDataTypeUniformVariable(const char* name, bool value) const
		{
			glUniform1i(glGetUniformLocation(shader_program_identity_, name), (int)value);
		}
		void Shader::SetIntegerDataTypeUniformVariable(const std::string& name, int value) const
		{
			glUniform1i(glGetUniformLocation(shader_program_identity_, name.c_str()), value);
		}
		void Shader::SetIntegerDataTypeUniformVariable(const char* name, int value) const
		{
			glUniform1i(glGetUniformLocation(shader_program_identity_, name), value);
		}
		void Shader::SetFloatDataTypeUniformVariable(const std::string& name, float value) const
		{
			glUniform1f(glGetUniformLocation(shader_program_identity_, name.c_str()), value);
		}
		void Shader::SetFloatDataTypeUniformVariable(const char* name, float value) const
		{
			glUniform1f(glGetUniformLocation(shader_program_identity_, name), value);
		}
		void Shader::SetVector2TypeUniformVariable(const std::string& name, glm::vec2& value) const
		{
			glUniform2fv(glGetUniformLocation(shader_program_identity_, name.c_str()), 1, &value[0]);
		}
		void Shader::SetVector2TypeUniformVariable(const char* name, glm::vec2& value) const
		{
			glUniform2fv(glGetUniformLocation(shader_program_identity_, name), 1, &value[0]);
		}
		void Shader::SetVector2TypeUniformVariable(const std::string& name, float x, float y) const
		{
			glUniform2f(glGetUniformLocation(shader_program_identity_, name.c_str()), x, y);
		}
		void Shader::SetVector2TypeUniformVariable(const char* name, float x, float y) const
		{
			glUniform2f(glGetUniformLocation(shader_program_identity_, name), x, y);
		}
		void Shader::SetVector3TypeUniformVariable(const std::string& name, glm::vec3& value) const
		{
			glUniform3fv(glGetUniformLocation(shader_program_identity_, name.c_str()), 1, &value[0]);
		}
		void Shader::SetVector3TypeUniformVariable(const char* name, glm::vec3& value) const
		{
			glUniform3fv(glGetUniformLocation(shader_program_identity_, name), 1, &value[0]);
		}
		void Shader::SetVector3TypeUniformVariable(const std::string& name, float x, float y, float z) const
		{
			glUniform3f(glGetUniformLocation(shader_program_identity_, name.c_str()), x, y, z);
		}
		void Shader::SetVector3TypeUniformVariable(const char* name, float x, float y, float z) const
		{
			glUniform3f(glGetUniformLocation(shader_program_identity_, name), x, y, z);
		}
		void Shader::SetVector4TypeUniformVariable(const std::string& name, glm::vec4& value) const
		{
			glUniform4fv(glGetUniformLocation(shader_program_identity_, name.c_str()), 1, &value[0]);
		}
		void Shader::SetVector4TypeUniformVariable(const char* name, glm::vec4& value) const
		{
			glUniform4fv(glGetUniformLocation(shader_program_identity_, name), 1, &value[0]);
		}
		void Shader::SetVector4TypeUniformVariable(const std::string& name, 
			float x, float y, float z, float w) const
		{
			glUniform4f(glGetUniformLocation(shader_program_identity_, name.c_str()), x, y, z, w);
		}
		void Shader::SetVector4TypeUniformVariable(const char* name,
			float x, float y, float z, float w) const
		{
			glUniform4f(glGetUniformLocation(shader_program_identity_, name), x, y, z, w);
		}
		void Shader::SetMatrix2TypeUniformVariable(const std::string& name, const glm::mat2& mat) const
		{
			glUniformMatrix2fv(glGetUniformLocation(shader_program_identity_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}
		void Shader::SetMatrix2TypeUniformVariable(const char* name, const glm::mat2& mat) const
		{
			glUniformMatrix2fv(glGetUniformLocation(shader_program_identity_, name), 1, GL_FALSE, &mat[0][0]);
		}
		void Shader::SetMatrix3TypeUniformVariable(const std::string& name, const glm::mat3& mat) const
		{
			glUniformMatrix3fv(glGetUniformLocation(shader_program_identity_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}
		void Shader::SetMatrix3TypeUniformVariable(const char* name, const glm::mat3& mat) const
		{
			glUniformMatrix3fv(glGetUniformLocation(shader_program_identity_, name), 1, GL_FALSE, &mat[0][0]);
		}
		void Shader::SetMatrix4TypeUniformVariable(const std::string& name, const glm::mat4& mat) const
		{
			glUniformMatrix4fv(glGetUniformLocation(shader_program_identity_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		}
		void Shader::SetMatrix4TypeUniformVariable(const char* name, const glm::mat4& mat) const
		{
			glUniformMatrix4fv(glGetUniformLocation(shader_program_identity_, name), 1, GL_FALSE, &mat[0][0]);
		}

	} // namespace object
} // namespace gdh_engine