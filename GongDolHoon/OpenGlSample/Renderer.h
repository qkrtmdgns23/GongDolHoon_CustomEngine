#ifndef RENDERER_H
#define RENDERER_H

#include "include/GL/glew.h"		
#include "include/GLFW/glfw3.h" 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Camera.h"

class Object;

class Renderer
{
public:
	Renderer(const char* title, int window_width, int window_height,
		const int gl_major_version, const int gl_minor_version, cam_data_t cam_data);
	~Renderer();

	void prepare_render();
	void render_object(Object* render_target_object);
	void end_render();
	
	bool is_window_close();

	GLFWwindow* get_window() const;

private:
	// version
	const int GL_MAJOR_VER;
	const int GL_MINOR_VER;

	// window field
	int window_width_;
	int window_height_;
	GLFWwindow* window_;
	const char* window_title_;

	// Camera 
	// there are no boundary between main and sub camera in this assignments. 
	Camera* main_camera_;

	void init_GLFW();
	void init_window();
	void init_GLEW();
	void init_openGL_options();
};

#endif /* RENDERER_H */
