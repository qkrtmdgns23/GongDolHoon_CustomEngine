#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <vector>

#include "include/GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// it's options of texture type, 
// this enumerator used in object's constructor
typedef enum texture_load_type
{
	DDS = 0,
	BMP,
}tex_load_type_t;

class FileManager
{
public:
	// for shader (vertex, fragment)
	GLuint load_shaders(const char* vertex_file_path, const char* fragment_file_path);

	// for texture
	GLuint load_dds(const char* dds_path);
	GLuint load_bmp(const char* bmp_path);

	// for mesh
	bool load_obj(const char* obj_path, std::vector<glm::vec3>& out_sphere_vertices, std::vector<glm::vec2>& out_sphere_uvs, std::vector<glm::vec3>& out_sphere_normals);


	static FileManager* get_instance()
	{
		if (instance == (void*)0)
		{
			instance = new FileManager();
		}
		return instance;
	}

private:
	/* FileManager was written as a dynamic singleton */
	/* https://vallista.tistory.com/entry/1-Singleton-Pattern-in-C */
	FileManager() {}
	FileManager(const FileManager& other) {}
	~FileManager() {}

	static FileManager* instance;
};

#endif /* FILE_MANAGER_H */
