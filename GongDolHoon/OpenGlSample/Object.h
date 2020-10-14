#ifndef GDH_ENGINE_OBJECT_H
#define GDH_ENGINE_OBJECT_H

#include <string>
#include <vector>

// library
#include "glm/glm.hpp"

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
				const char* obj_path, TextureType dimension, TextureType alpha);
			Object(std::string vertex_path, std::string fragment_path, std::string texture_path,
				const char* obj_path, TextureType dimension, TextureType alpha);
			~Object();

			void SetupMesh();
			void SetTextureUniformToShader(std::string tex_uniform_name, unsigned int tex_num);
			void SetTextureUniformToShader(const char* tex_uniform_name, unsigned int tex_num);
			void ActiveTextureRendering();
			void Render();

		private:
			Texture* object_texture_;
			Shader* object_shader_;
			Mesh* object_mesh_;
			
			glm::mat4 object_model_matrix_;
			glm::mat4 object_view_matrix_;
			glm::mat4 object_projection_matrix_;
		};
	}	// namespace object
}	// namespace gdh_engine

#endif // GDH_ENGINE_OBJECT_H