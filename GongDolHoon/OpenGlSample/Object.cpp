// library
#include "glm/gtc/matrix_transform.hpp"

// custom header
#include "object.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "renderer.h"
#include "transform.h"

namespace gdh_engine {
	namespace object {
		Object::Object(const char* vertex_path, const char* fragment_path, const char* texture_path,
			const char* obj_path, obj_transform_t target_transform,
			TextureType dimension, TextureType alpha)
		{
			object_shader_ = new Shader(vertex_path, fragment_path);
			object_texture_ = new Texture(texture_path, dimension, alpha);
			object_mesh_ = new Mesh(obj_path);
			object_transform_ = new Transform(target_transform);

			object_mesh_->SetUpMesh();
			SetTextureUniformToShader("texture1", 0);
		}
		Object::Object(std::string vertex_path, std::string fragment_path, std::string texture_path,
			const char* obj_path, obj_transform_t target_transform,
			TextureType dimension, TextureType alpha)
		{
			object_shader_ = new Shader(vertex_path, fragment_path);
			object_texture_ = new Texture(texture_path, dimension, alpha);
			object_mesh_ = new Mesh(obj_path);
			object_transform_ = new Transform(target_transform);

			object_mesh_->SetUpMesh();
			SetTextureUniformToShader("texture1", 0);
		}
		Object::Object(const char* vertex_path, const char* fragment_path, const char* texture_path,
			const char* obj_path, TextureType dimension, TextureType alpha)
		{
			object_shader_ = new Shader(vertex_path, fragment_path);
			object_texture_ = new Texture(texture_path, dimension, alpha);
			object_mesh_ = new Mesh(obj_path);
			object_transform_ = new Transform();

			object_mesh_->SetUpMesh();
			SetTextureUniformToShader("texture1", 0);
		}
		Object::Object(std::string vertex_path, const char* fragment_path, const char* texture_path,
			const char* obj_path, TextureType dimension, TextureType alpha)
		{
			object_shader_ = new Shader(vertex_path, fragment_path);
			object_texture_ = new Texture(texture_path, dimension, alpha);
			object_mesh_ = new Mesh(obj_path);
			object_transform_ = new Transform();

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

		void Object::SetObjectTransform(obj_transform_t target_transform)
		{
			object_transform_->set_position(target_transform.position);
			object_transform_->set_rotation(target_transform.rotation);
			object_transform_->set_scale(target_transform.scale);
		}
		void Object::SetObjectPosition(glm::vec3 target_position)
		{
			object_transform_->set_position(target_position);
		}
		void Object::SetObjectRotation(glm::vec3 target_rotation)
		{
			object_transform_->set_rotation(target_rotation);
		}
		void Object::SetObjectScale(glm::vec3 target_scale)
		{
			object_transform_->set_scale(target_scale);
		}
		void Object::MoveObject(glm::vec3 position)
		{
			object_transform_->Move(position);
		}
		void Object::RotateObject(glm::vec3 rotation)
		{
			object_transform_->Rotate(rotation);
		}
		void Object::ResizeObject(glm::vec3 scale)
		{
			object_transform_->Resize(scale);
		}

		void Object::SendProjectionAndViewMatrixToShader(glm::mat4 projection, glm::mat4 view)
		{
			object_shader_->SetMatrix4TypeUniformVariable("projection", projection);
			object_shader_->SetMatrix4TypeUniformVariable("view", view);
		}

		void Object::Render()
		{
			object_shader_->SetMatrix4TypeUniformVariable("model", object_transform_->get_model_matrix());

			glBindVertexArray(object_mesh_->get_vertex_array_object_identity());
			glDrawArrays(GL_TRIANGLES, 0, object_mesh_->get_num_of_vertices());
		}

		void Object::SetTextureActive()
		{
			object_texture_->SetActive();
		}

		void Object::SetTransformActive()
		{
			object_transform_->SetActive();
		}

		void Object::SetMeshActive()
		{
			object_mesh_->SetActive();
		}

		void Object::SetTextureUnActive()
		{
			object_texture_->SetUnActive();
		}

		void Object::SetTransformUnActive()
		{
			object_transform_->SetUnActive();
		}

		void Object::SetMeshUnActive()
		{
			object_mesh_->SetUnActive();
		}

	}	// namespace object
}	// namespace gdh_engine