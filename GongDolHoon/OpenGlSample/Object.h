#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
// library
#include "include/GL/glew.h"		
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
// custom header
#include "FileManager.h"	// if we don't include fileManager.h in object.h, compiler can't find the reference of object field
#include "Transform.h"

class Shader;
class Texture;
class Mesh;
class Camera;

class Object
{
public:
	// Constructor and destructor
	Object(const char* vertex_shader_path, const char* fragment_shader_path, const char* texture_path, tex_load_type_t texture_type, const char* obj_path);
	virtual ~Object();

	// Property for data field
	GLuint get_shader_id() const;
	GLuint get_texture_id() const;
	GLuint get_vertex_buffer_object() const;
	GLuint get_uv_buffer_object() const;
	GLuint get_vertex_array_object() const;

	std::vector<glm::vec3> get_object_vertices() const;
	std::vector<glm::vec3> get_object_normals() const;
	std::vector<glm::vec2> get_object_uvs() const;

	void update_transform_inform(obj_transform_t obj_transform_inform);
	void update_texture_inform();
	void update_view_matrix(Camera* world_camera);
	void update_projection_matrix();

private:
	Shader* object_shader_;
	Texture* object_texture_;
	Mesh* object_mesh_;
	Transform* object_transform_;
};

#endif /* OBJECT_H */
