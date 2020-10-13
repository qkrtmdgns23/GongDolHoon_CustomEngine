// library
#include "include/GL/glew.h"	

// custom header
#include "mesh.h"
#include "file_manager.h"

namespace gdh_engine {
	namespace object {
		Mesh::Mesh(std::string obj_path)
		{
			manager::file::FileManager::get_instance()->Load3DModelFromObj(obj_path, vertices_, uvs_,normals_);

			is_vertex_array_object_invoke_ = false;
		}
		Mesh::~Mesh()
		{
			glDeleteVertexArrays(1, &vertex_array_object_identity_);
			glDeleteBuffers(1, &vertex_buffer_object_identity_);
		}

		void Mesh::SetUpMesh()
		{
			GenerateAndBindVertexArrayObject();
			GenerateAndBindVertexBufferObject();
			EnableFloatTypeVertexAttribArray(0, 3, 8, 0, object::AttribDataType::kGdhFloat, false);
			EnableFloatTypeVertexAttribArray(1, 2, 8, 3, object::AttribDataType::kGdhFloat, false);
			UnbindVertexBufferObject();
			UnbindVertexArrayObject();
		}

		void Mesh::GenerateAndBindVertexArrayObject()
		{
			is_vertex_array_object_invoke_ = true;
			glGenVertexArrays(1, &vertex_array_object_identity_);
			glBindVertexArray(vertex_array_object_identity_);
		}

		void Mesh::GenerateAndBindVertexBufferObject()
		{
			if (is_vertex_array_object_invoke_)
			{
				glGenBuffers(1, &vertex_buffer_object_identity_);
				glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object_identity_);
				glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(glm::vec3), &vertices_[0], GL_STATIC_DRAW);
				glBufferData(GL_ARRAY_BUFFER, uvs_.size() * sizeof(glm::vec2), &uvs_[0], GL_STATIC_DRAW);
				glBufferData(GL_ARRAY_BUFFER, normals_.size() * sizeof(glm::vec3), &normals_[0], GL_STATIC_DRAW);
			}
			else
			{
				fprintf(stdout, "You should invoke GenerateAndBindVertexArrayObject function first.\n");
			}
		}

		void Mesh::EnableFloatTypeVertexAttribArray(const int location, const int vertex_attrib_size,
			const int stride, const int offset, AttribDataType data_type, bool is_normalization)
		{
			glVertexAttribPointer(location, vertex_attrib_size, (int)data_type, is_normalization,
				stride * sizeof(float), (void*)(offset * sizeof(float)));
			glEnableVertexAttribArray(location);
		}

		void Mesh::UnbindVertexBufferObject()
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void Mesh::UnbindVertexArrayObject()
		{
			glBindVertexArray(0);
		}

	} // namespace object
} // namespace gdh_engine