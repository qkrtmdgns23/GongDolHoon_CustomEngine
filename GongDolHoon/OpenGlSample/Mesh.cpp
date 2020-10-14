// library
#include "include/GL/glew.h"	

// custom header
#include "mesh.h"
#include "file_manager.h"

namespace gdh_engine {
	namespace object {
		Mesh::Mesh(std::string obj_path)
		{
			unsigned int *get_num_of_vertices = &num_of_vertices_;
			manager::file::FileManager::get_instance()->Load3DModelFromObj(obj_path, vertices_, uvs_,normals_, get_num_of_vertices);
			is_vertex_array_object_invoke_ = false;
			this->vertex_array_ = new VertexInformation[this->num_of_vertices_];
			for (size_t i = 0; i < num_of_vertices_; ++i)
			{
				vertex_array_[i].position = vertices_[i];
				vertex_array_[i].normal = normals_[i];
				vertex_array_[i].texture_coordinate = uvs_[i];
			}

		}
		Mesh::Mesh(const char* obj_path)
		{
			unsigned int* get_num_of_vertices = &num_of_vertices_;
			manager::file::FileManager::get_instance()->Load3DModelFromObj(obj_path, vertices_, uvs_, normals_, get_num_of_vertices);
			is_vertex_array_object_invoke_ = false;
			this->vertex_array_ = new VertexInformation[this->num_of_vertices_];
			for (size_t i = 0; i < num_of_vertices_; ++i)
			{
				vertex_array_[i].position = vertices_[i];
				vertex_array_[i].normal = normals_[i];
				vertex_array_[i].texture_coordinate = uvs_[i];
			}

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

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (GLvoid*)offsetof(vertex_t, position));
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (GLvoid*)offsetof(vertex_t, texture_coordinate));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (GLvoid*)offsetof(vertex_t, normal));

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
				glBufferData(GL_ARRAY_BUFFER, this->num_of_vertices_ * sizeof(vertex_t), this->vertex_array_, GL_STATIC_DRAW);
			}
			else
			{
				fprintf(stdout, "You should invoke GenerateAndBindVertexArrayObject function first.\n");
			}
		}

		//void Mesh::EnableFloatTypeVertexAttribArray(const int location, const int vertex_attrib_size,
		//	const int stride, const int offset, AttribDataType data_type, bool is_normalization)
		//{
		//	glVertexAttribPointer(location, vertex_attrib_size, (int)data_type, is_normalization,
		//		stride * sizeof(float), (void*)(offset * sizeof(float)));
		//	glEnableVertexAttribArray(location);
		//}

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