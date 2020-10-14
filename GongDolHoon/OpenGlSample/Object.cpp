// library
#include "glm/gtc/matrix_transform.hpp"

// custom header
#include "object.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "renderer.h"

namespace gdh_engine {
	namespace object {
		Object::Object(const char* vertex_path, const char* fragment_path, const char* texture_path, 
			const char* obj_path, TextureType dimension, TextureType alpha)
		{
			object_shader_ = new Shader(vertex_path, fragment_path);
			object_texture_ = new Texture(texture_path, dimension, alpha);
			object_mesh_ = new Mesh(obj_path);

			object_mesh_->SetUpMesh();
			SetTextureUniformToShader("texture1", 0);
		}
		Object::Object(std::string vertex_path, std::string fragment_path, std::string texture_path,
			const char* obj_path, TextureType dimension, TextureType alpha)
		{
			object_shader_ = new Shader(vertex_path, fragment_path);
			object_texture_ = new Texture(texture_path, dimension, alpha);
			object_mesh_ = new Mesh(obj_path);

			object_mesh_->SetUpMesh();
			SetTextureUniformToShader("texture1", 0);
		}
		Object::~Object()
		{
			delete object_shader_;
			delete object_texture_;
			delete object_mesh_;
		}

		void Object::SetupMesh()
		{
			object_mesh_->SetUpMesh();
		}
		void Object::SetTextureUniformToShader(std::string tex_uniform_name, unsigned int tex_num)
		{
			object_shader_->UseShader();
			object_shader_->SetIntegerDataTypeUniformVariable(tex_uniform_name, tex_num);
		}
		void Object::SetTextureUniformToShader(const char* tex_uniform_name, unsigned int tex_num)
		{
			object_shader_->UseShader();
			object_shader_->SetIntegerDataTypeUniformVariable(tex_uniform_name, tex_num);
		}
		void Object::ActiveTextureRendering()
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, object_texture_->get_texture_id());
		}
		void Object::Render()
		{
			object_model_matrix_ = glm::mat4(1.f);
			object_view_matrix_ = glm::mat4(1.f);
			object_projection_matrix_ = glm::mat4(1.f);

			object_shader_->UseShader();

			object_model_matrix_ = glm::rotate(object_model_matrix_, (float)glfwGetTime(), glm::vec3(0.5f, 1.f, 0.f));
			object_view_matrix_ = glm::translate(object_view_matrix_, glm::vec3(0.f, 0.f, -10.f));
			object_projection_matrix_ = glm::perspective(glm::radians(45.0f), 
				(float)1028/724, 0.1f, 100.f);
			object_shader_->SetMatrix4TypeUniformVariable("model", object_model_matrix_);
			object_shader_->SetMatrix4TypeUniformVariable("view", object_view_matrix_);
			object_shader_->SetMatrix4TypeUniformVariable("projection", object_projection_matrix_);

			glBindVertexArray(object_mesh_->get_vertex_array_object_identity());
			glDrawArrays(GL_TRIANGLES, 0, object_mesh_->get_num_of_vertices());
		}

	}	// namespace object
}	// namespace gdh_engine