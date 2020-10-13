#ifndef GDH_ENGINE_MESH_H
#define GDH_ENGINE_MESH_H

#include <vector>
#include <string>
// library
#include "glm/glm.hpp"
#include "include/GLFW/glfw3.h" 

namespace gdh_engine {
	namespace object {
		enum class AttribDataType;

		class Mesh
		{
		public:
			Mesh(std::string obj_path);
			~Mesh();

			void SetUpMesh();

			GLuint get_vertex_array_object_identity() const
			{
				return vertex_array_object_identity_;
			}
			GLuint get_vertex_buffer_object_identity() const
			{
				return vertex_buffer_object_identity_;
			}

		private:
			void GenerateAndBindVertexArrayObject();
			void GenerateAndBindVertexBufferObject();
			void EnableFloatTypeVertexAttribArray(const int location,
				const int vertex_attrib_size, const int stride, const int offset,
				AttribDataType data_type, bool is_normalization);
			void UnbindVertexBufferObject();
			void UnbindVertexArrayObject();

			GLuint vertex_array_object_identity_;
			GLuint vertex_buffer_object_identity_;

			std::vector<glm::vec3> vertices_;
			std::vector<glm::vec3> normals_;
			std::vector<glm::vec2> uvs_;

			// this is value for prevent invoke sequence violation.
			bool is_vertex_array_object_invoke_;
		};

		enum class AttribDataType
		{
			kGdhByte = GL_BYTE,
			kGdhUnsignedByte = GL_UNSIGNED_BYTE,
			kGdhShort = GL_SHORT,
			kGdhUnsignedShort = GL_UNSIGNED_SHORT,
			kGdhInt = GL_INT,
			kGdhUnsignedInt = GL_UNSIGNED_INT,
			kGdhFloat = GL_FLOAT,
			kGdh2Bytes = GL_2_BYTES,
			kGdh3Bytes = GL_3_BYTES,
			kGdh4Bytes = GL_4_BYTES,
			kGdhDouble = GL_DOUBLE,
		};
	} // namespace object
} // namespace gdh_engine

#endif // GDH_ENGINE_MESH_H