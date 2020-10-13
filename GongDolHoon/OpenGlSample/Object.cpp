// custom header
#include "object.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"

namespace gdh_engine {
	namespace object {
		Object::Object(const char* vertex_path, const char* fragment_path, const char* texture_path,
			TextureType dimension, TextureType alpha)
		{	
			object_shader_ = new Shader(vertex_path, fragment_path);
			object_texture_ = new Texture(texture_path, dimension, alpha);
			object_mesh_ = new Mesh();
		}
		Object::Object(std::string vertex_path, std::string fragment_path, std::string texture_path,
			TextureType dimension, TextureType alpha)
		{
			object_shader_ = new Shader(vertex_path, fragment_path);
			object_texture_ = new Texture(texture_path, dimension, alpha);
			object_mesh_ = new Mesh();
		}
		Object::~Object()
		{
			delete object_shader_;
			delete object_texture_;
			delete object_mesh_;
		}


	}	// namespace object
}	// namespace gdh_engine