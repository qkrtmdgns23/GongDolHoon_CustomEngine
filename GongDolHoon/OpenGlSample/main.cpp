#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>

// library
#include "include/GL/glew.h"		
#include "include/GLFW/glfw3.h" 
#include "glm/glm.hpp"

// customize header file
#include "FileManager.h"
#include "Object.h"
#include "Renderer.h"
#include "Camera.h"

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib-vc2017/glew32.lib")
#pragma comment(lib, "lib-vc2017/glfw3.lib")

using namespace glm;
using namespace std;

int main(void)
{
	cam_data_t camera_position = { glm::vec3(0, 1, 0), glm::vec3(40, 30, 30) };
	Renderer* engine_renderer = new Renderer("GongDolHoonEngine_ver1.0.0", 1024, 768, 3, 3, camera_position);

	Object* temp_cube = new Object("resource/shaders/cube_vertex.shader", "resource/shaders/cube_fragment.shader",
		"resource/bmp/Earth.bmp", tex_load_type_t::BMP, "resource/obj/cube.obj");
	
	obj_transform_t initialize_cube_transform = {glm::vec3(5.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(10.f)};
	temp_cube->update_transform_inform(initialize_cube_transform);
	
	while (engine_renderer->is_window_close())
	{
		engine_renderer->prepare_render();
		engine_renderer->render_object(temp_cube);
		engine_renderer->end_render();
	}
	delete temp_cube;
	delete engine_renderer;

	return 0;
}