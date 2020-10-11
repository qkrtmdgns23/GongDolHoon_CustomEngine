#ifndef TEXTURE_H
#define TEXTURE_H

// library
#include "include/GL/glew.h"		

// for using tex_load_type_t
#include "FileManager.h"

class Texture
{
public:
	Texture(const char* texture_path, tex_load_type_t texture_type);
	~Texture();

	GLuint get_texture_id() const;

private:
	GLuint texture_id_;

};

#endif /* TEXTURE_H */
