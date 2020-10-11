#ifndef MESH_H
#define MESH_H

#include <vector>
// library
#include "include/GL/glew.h"	
#include "glm/glm.hpp"

class Mesh
{
public:
	Mesh(const char* obj_path);
	~Mesh();

	std::vector<glm::vec3> get_vertices() const;
	std::vector<glm::vec2> get_uvs() const;
	std::vector<glm::vec3> get_normals() const;

	GLuint get_vertex_array_object() const;
	GLuint get_vertex_buffer_object() const;
	GLuint get_uv_buffer_object() const;

private:
	GLuint vertex_array_object_;
	GLuint vertex_buffer_object_;
	GLuint uv_buffer_object_;
	GLuint normal_buffer_object_;

	std::vector<glm::vec3> vertices_;
	std::vector<glm::vec3> normals_;
	std::vector<glm::vec2> uvs_;

	void init_vertex_array_object();
	void init_and_send_vertex_buffer();
	void init_and_send_uv_buffer();
	void init_and_send_normal_buffer();

	void vertex_attrib_pointer_and_enable_vertex_array();
};

#endif /* MESH_H */
