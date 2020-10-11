#include "Texture.h"
#include "FileManager.h"


Texture::Texture(const char* texture_path, tex_load_type_t texture_type)
{
	if (texture_type == tex_load_type_t::DDS)
	{
		texture_id_ = FileManager::get_instance()->load_dds(texture_path);
	}
	else if (texture_type == tex_load_type_t::BMP)
	{
		texture_id_ = FileManager::get_instance()->load_bmp(texture_path);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->texture_id_);
}

GLuint Texture::get_texture_id() const
{
	return texture_id_;
}