#include <iostream>

#include "Renderer.h"
#include "Object.h"

Renderer::Renderer(const char* title, int window_width, int window_height,
	const int gl_major_version, const int gl_minor_version, cam_data_t cam_data)
	: window_title_(title), GL_MAJOR_VER(gl_major_version), GL_MINOR_VER(gl_minor_version)
{
	window_width_ =  window_width;
	window_height_ = window_height;

	this->init_GLFW();
	this->init_window();
	this->init_GLEW();
	this->init_openGL_options();

	main_camera_ = new Camera(cam_data.camera_position, cam_data.world_ceiling);
}

Renderer::~Renderer()
{
	glfwTerminate();
}

void Renderer::init_GLFW()
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		glfwTerminate();
	}
}

void Renderer::init_GLEW()
{
	glewExperimental = true; // Needed for core profile
	
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		glfwTerminate();
	}
}

void Renderer::init_window()
{
	// I don't know about second argument which takes four.
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_MAJOR_VER);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_MINOR_VER);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window_ = glfwCreateWindow(window_width_, window_height_, window_title_, NULL, NULL);
	if (window_ == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
	}
	glfwMakeContextCurrent(this->window_);
}

void Renderer::init_openGL_options()
{
	glfwSetInputMode(window_, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

}

bool Renderer::is_window_close()
{
	return (glfwGetKey(window_, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window_) == 0);
}

void Renderer::prepare_render()
{
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render_object(Object* render_target_object)
{
	glUseProgram(render_target_object->get_shader_id());
	glBindVertexArray(render_target_object->get_vertex_array_object());
	glDrawArrays(GL_TRIANGLES, 0, render_target_object->get_object_vertices().size());
	render_target_object->update_texture_inform();
	render_target_object->update_view_matrix(this->main_camera_);
	render_target_object->update_projection_matrix();
}

void Renderer::end_render()
{
	glfwSwapBuffers(window_);
	glfwPollEvents();

	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLFWwindow* Renderer::get_window() const
{
	return window_;
}
