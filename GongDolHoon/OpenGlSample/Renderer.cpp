#include <iostream>

// library
#include "include/GL/glew.h"	

// custom header
#include "renderer.h"

namespace gdh_engine {
	namespace manager {
		Renderer::Renderer(const char* title, const unsigned int kMajorVersion, const unsigned int kMinorVersion,
			const unsigned int kWindowHeight, const unsigned int kWindowWidth)
			: kGlfwContextMajorVersion(kMajorVersion), kGlfwContextMinorVersion(kMinorVersion)
		{
			this->engine_window_title_ = title;
			this->window_height_ = kWindowHeight;
			this->window_width_ = kWindowWidth;

			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, kGlfwContextMajorVersion);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, kGlfwContextMinorVersion);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			this->engine_window_ = glfwCreateWindow(window_width_, window_height_, engine_window_title_.c_str(), NULL, NULL);
			if (engine_window_ == NULL)
			{
				fprintf(stderr, "Failed to Create Glfw Window.\n");
				glfwTerminate();
			}

			glfwMakeContextCurrent(engine_window_);
			glfwSetFramebufferSizeCallback(engine_window_, ResizeWindowFrameBuffer);

			glewExperimental = true; // Needed for core profile

			if (glewInit() != GLEW_OK) {
				fprintf(stderr, "Failed to initialize GLEW\n");
				glfwTerminate();
			}

			glEnable(GL_DEPTH_TEST);
		}

		Renderer::Renderer(std::string title, const unsigned int kMajorVersion, const unsigned int kMinorVersion,
			const unsigned int kWindowHeight, const unsigned int kWindowWidth)
			: kGlfwContextMajorVersion(kMajorVersion), kGlfwContextMinorVersion(kMinorVersion)
		{
			this->engine_window_title_ = title;
			this->window_height_ = kWindowHeight;
			this->window_width_ = kWindowWidth;

			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, kGlfwContextMajorVersion);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, kGlfwContextMinorVersion);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			engine_window_ = glfwCreateWindow(window_width_, window_height_, engine_window_title_.c_str(), NULL, NULL);
			if (engine_window_ == NULL)
			{
				fprintf(stderr, "Failed to Create Glfw Window.\n");
				glfwTerminate();
			}

			glfwMakeContextCurrent(engine_window_);
			glfwSetFramebufferSizeCallback(engine_window_, ResizeWindowFrameBuffer);

			glewExperimental = true; // Needed for core profile

			if (glewInit() != GLEW_OK) {
				fprintf(stderr, "Failed to initialize GLEW\n");
				glfwTerminate();
			}

			glEnable(GL_DEPTH_TEST);
		}

		Renderer::~Renderer()
		{
			glfwTerminate();
		}

		void Renderer::ClearWindowToRender()
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Renderer::SwapBuffearsOnWindow()
		{
			glfwSwapBuffers(engine_window_);
			glfwPollEvents();
		}

		bool Renderer::IsWindowShouldClose()
		{
			if (glfwWindowShouldClose(this->engine_window_))
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		void Renderer::ResizeWindowFrameBuffer(GLFWwindow* window, int fbw, int fbh)
		{
			glViewport(0, 0, fbw, fbh);
		}
	} // namespace manager
} // namespace gdh_engine