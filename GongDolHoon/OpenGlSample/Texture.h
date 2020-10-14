#ifndef GDH_ENGINE_TEXTURE_H
#define GDH_ENGINE_TEXTURE_H

#include <string>

// library
#include "include/GL/glew.h"	

namespace gdh_engine {
	namespace object {
		enum class TextureType;

		class Texture
		{
		public:
			Texture(std::string texture_path, TextureType type_of_texture, TextureType alpha_data_type);
			Texture(const char* texture_path, TextureType type_of_texture, TextureType alpha_data_type);
			~Texture() {}

			GLuint get_texture_id() const
			{
				return texture_id_;
			}

		private:
			GLuint texture_id_;

			int texture_width_;
			int texture_height_;
			int texture_nr_channels_;

		};

		enum class TextureType
		{
			k2DimensionalTexture = 0,
			k3DimensionalTexture,
			kRGBTexture,
			kRGBATexture,
		};

	} // namespace object
} // namespace gdh_engine

#endif // GDH_ENGINE_TEXTURE_H