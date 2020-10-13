#ifndef GDH_ENGINE_OBJECT_H
#define GDH_ENGINE_OBJECT_H

#include <string>
#include <vector>

namespace gdh_engine {
	namespace object {
		class Texture;
		class Shader;
		class Mesh;
		enum class TextureType;

		class Object
		{
		public:
			Object(const char* vertex_path, const char* fragment_path, const char* texture_path, 
				TextureType dimension, TextureType alpha);
			Object(std::string vertex_path, std::string fragment_path, std::string texture_path,
				TextureType dimension, TextureType alpha);
			~Object();

		private:
			Texture* object_texture_;
			Shader* object_shader_;
			Mesh* object_mesh_;
			
		};
	}	// namespace object
}	// namespace gdh_engine

#endif // GDH_ENGINE_OBJECT_H