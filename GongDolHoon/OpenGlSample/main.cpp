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
#include "input_manager.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib-vc2017/glew32.lib")
#pragma comment(lib, "lib-vc2017/glfw3.lib")

using namespace glm;
using namespace std;
using namespace gdh_engine;

const int kScreenWidth = 1028;
const int kScreenHeight = 724;
const int kOpenGLMajorVersion = 3;
const int kOpenGLMinorVersion = 3;

int main(void)
{
	manager::Renderer* gdh_renderer = new manager::Renderer
        ("GongDolHoon_CustomEngine", kOpenGLMajorVersion, kOpenGLMinorVersion, kScreenHeight, kScreenWidth);
    object::Shader* triangle_shader = 
        new object::Shader("resource/shaders/triangle_vs.glsl", "resource/shaders/triangle_fs.glsl");
    object::Mesh* temp_mesh = new object::Mesh("resource/obj/cube.obj");

    temp_mesh->SetUpMesh();

    object::Texture* new_texture1 = new object::Texture("resource/jpg/container.jpg", object::TextureType::k2DTexture, object::TextureType::kRGB);
   
    triangle_shader->UseShader();
    triangle_shader->SetIntegerDataTypeUniformVariable("texture1", 0);

	while (gdh_renderer->IsWindowShouldClose() == false)
	{
		manager::InputManager::get_instance()->ProcessInput(gdh_renderer->get_engine_window());
		
		gdh_renderer->ClearWindowToRender();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, new_texture1->get_texture_id());

        triangle_shader->UseShader();

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.f, 0.f));
        view = glm::translate(view, glm::vec3(0.f, 0.f, -10.f));
        projection = glm::perspective(glm::radians(45.0f), (float)kScreenWidth/kScreenHeight, 0.1f, 100.f);

        triangle_shader->SetMatrix4TypeUniformVariable("model", model);
        triangle_shader->SetMatrix4TypeUniformVariable("view", view);
        triangle_shader->SetMatrix4TypeUniformVariable("projection", projection);
        
        // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glBindVertexArray(temp_mesh->get_vertex_array_object_identity()); 
        glDrawArrays(GL_TRIANGLES, 0, 36);

        gdh_renderer->SwapBuffearsOnWindow();
	}

    delete temp_mesh;
    delete triangle_shader;
	delete gdh_renderer;
	
    return 0;
}
