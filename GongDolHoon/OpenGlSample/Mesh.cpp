#include "Mesh.h"
#include "FileManager.h"

Mesh::Mesh(const char* obj_path)
{
	FileManager::get_instance()->load_obj(obj_path, vertices_, uvs_, normals_);

	init_vertex_array_object();
	init_and_send_vertex_buffer();
	init_and_send_uv_buffer();
	init_and_send_normal_buffer();
	vertex_attrib_pointer_and_enable_vertex_array();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &this->vertex_array_object_);
	glDeleteBuffers(1, &this->vertex_buffer_object_);
	glDeleteBuffers(1, &this->uv_buffer_object_);
}

void Mesh::init_vertex_array_object()
{
	glGenVertexArrays(1, &vertex_array_object_);
	glBindVertexArray(vertex_array_object_);
}

void Mesh::init_and_send_vertex_buffer()
{
	glGenBuffers(1, &vertex_buffer_object_);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_array_object_);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(glm::vec3), &vertices_[0], GL_STATIC_DRAW);
}

void Mesh::init_and_send_uv_buffer()
{
	glGenBuffers(1, &uv_buffer_object_);
	glBindBuffer(GL_ARRAY_BUFFER,uv_buffer_object_);
	glBufferData(GL_ARRAY_BUFFER, uvs_.size() * sizeof(glm::vec2), &uvs_[0], GL_STATIC_DRAW);
}

void Mesh::init_and_send_normal_buffer()
{
	glGenBuffers(1, &normal_buffer_object_);
	glBindBuffer(GL_ARRAY_BUFFER, normal_buffer_object_);
	glBufferData(GL_ARRAY_BUFFER, normals_.size() * sizeof(glm::vec3), &normals_[0], GL_STATIC_DRAW);
}

void Mesh::vertex_attrib_pointer_and_enable_vertex_array()
{
	// Vertex Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Vertex UV Coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)3);
	glEnableVertexAttribArray(1);
	// Vertex Normal Inform
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)5);
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
}

std::vector<glm::vec3> Mesh::get_vertices() const
{
	return vertices_;
}

std::vector<glm::vec2> Mesh::get_uvs() const
{
	return uvs_;
}

std::vector<glm::vec3> Mesh::get_normals() const
{
	return normals_;
}

GLuint Mesh::get_vertex_array_object() const
{
	return vertex_array_object_;
}

GLuint Mesh::get_vertex_buffer_object() const
{
	return vertex_buffer_object_;
}

GLuint Mesh::get_uv_buffer_object() const
{
	return uv_buffer_object_;
}
