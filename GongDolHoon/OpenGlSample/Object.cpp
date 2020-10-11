#include "Object.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Mesh.h"

Object::Object(const char* vertex_shader_path, const char* fragment_shader_path, const char* texture_path, tex_load_type_t texture_type, const char* obj_path)
{
	object_shader_ = new Shader(vertex_shader_path, fragment_shader_path);
	object_texture_ = new Texture(texture_path, texture_type);
	object_mesh_ = new Mesh(obj_path);
	object_transform_ = new Transform();
}

Object::~Object()
{
	delete object_shader_;
	delete object_texture_;
}

GLuint Object::get_shader_id() const
{
	return object_shader_->get_program_id();
}

GLuint Object::get_texture_id() const
{
	return object_texture_->get_texture_id();
}

GLuint Object::get_vertex_buffer_object() const
{
	return object_mesh_->get_vertex_buffer_object();
}

GLuint Object::get_uv_buffer_object() const
{
	return object_mesh_->get_uv_buffer_object();
}

GLuint Object::get_vertex_array_object() const
{
	return object_mesh_->get_vertex_array_object();
}

std::vector<glm::vec3> Object::get_object_vertices() const
{
	return object_mesh_->get_vertices();
}

std::vector<glm::vec3> Object::get_object_normals() const
{
	return object_mesh_->get_normals();
}

std::vector<glm::vec2> Object::get_object_uvs() const
{
	return object_mesh_->get_uvs();
}

void Object::update_transform_inform(obj_transform_t obj_transform_inform)
{
	// set this->obj_transform_
	object_transform_->set_position(obj_transform_inform.position);
	object_transform_->set_rotation(obj_transform_inform.rotation);
	object_transform_->set_scale(obj_transform_inform.scale);

	// update
	object_transform_->update_uniforms(object_shader_);
}

void Object::update_texture_inform()
{
	object_shader_->set_int("MyTextureSampler", 1);
}

void Object::update_view_matrix(Camera* world_camera)
{
	object_shader_->set_mat4("View", world_camera->get_view_matrix());
}

void Object::update_projection_matrix()
{
	// you should change this mat value while camera moved.
	glm::mat4 _temp_projection_mat;
	_temp_projection_mat = glm::perspective(glm::radians(45.0f), 4.5f / 3.0f, 0.1f, 100.0f);
	object_shader_->set_mat4("Projection", _temp_projection_mat);
}