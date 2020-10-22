// library
#include "include/GL/glew.h"		

// custom header
#include "renderer.h"
#include "texture.h"
#include "input_manager.h"
#include "object.h"
#include "sphere.h"
#include "camera.h"

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib-vc2017/glew32.lib")
#pragma comment(lib, "lib-vc2017/glfw3.lib")

using namespace glm;
using namespace std;
using namespace gdh_engine;

int main(void)
{   
    manager::Renderer* renderer = manager::Renderer::get_instance();
    object::Camera* camera = object::Camera::get_instance();
   /* object::Object* cube = new object::Object("resource/shaders/cube_vs.glsl", "resource/shaders/cube_fs.glsl", "resource/jpg/container.jpg", 
        "resource/obj/cube.obj",object::TextureType::k2DimensionalTexture, object::TextureType::kRGBTexture);
   */
   object::primitive::Sphere* cube = new  object::primitive::Sphere();

    cube->SetObjectPosition(glm::vec3(0.f, 0.f, 0.f));
    cube->SetObjectRotation(glm::vec3(45.0f, 45.0f, 0.0f));

    camera->set_camera_position(glm::vec3(0.f, 0.f, 10.0f));

	while (renderer->IsWindowShouldClose() == false)
	{
		manager::InputManager::get_instance()->ProcessInput(renderer->get_engine_window());
        renderer->ConvertCoordinatesForRender(camera, cube);
        cube->RotateObject(glm::vec3(glfwGetTime(), 0.f, 0.f));
        renderer->Render(cube);
	}
    renderer->ShutDown();
    delete cube;

    return 0;
}
