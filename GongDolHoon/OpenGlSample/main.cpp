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
#include "glm/gtc/matrix_transform.hpp"

// custom header
#include "renderer.h"
#include "texture.h"
#include "input_manager.h"
#include "object.h"
#include "camera.h"

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib-vc2017/glew32.lib")
#pragma comment(lib, "lib-vc2017/glfw3.lib")

using namespace glm;
using namespace std;
using namespace gdh_engine;

const unsigned int kOpenGLMajorVersion = 3;
const unsigned int kOpenGLMinorVersion = 3;

int main(void)
{   
    manager::Renderer* renderer = manager::Renderer::get_instance();
    object::Camera* camera = object::Camera::get_instance();
    object::Object* cube = new object::Object("resource/shaders/cube_vs.glsl", "resource/shaders/cube_fs.glsl", "resource/jpg/container.jpg", 
        "resource/obj/cube.obj",object::TextureType::k2DimensionalTexture, object::TextureType::kRGBTexture);
    
    cube->SetObjectPosition(glm::vec3(0.f, 0.f, 0.f));
    cube->SetObjectRotation(glm::vec3(45.0f, 45.0f, 0.0f));
    camera->set_camera_position(glm::vec3(0.f, 0.f, 10.0f));

	while (renderer->IsWindowShouldClose() == false)
	{
		manager::InputManager::get_instance()->ProcessInput(renderer->get_engine_window());
        renderer->ConvertCoordinatesForRender(camera, cube);
        renderer->Render(cube);
	}
    renderer->ShutDown();
    return 0;
}
