#ifndef GDH_ENGINE_RENDERER_H
#define GDH_ENGINE_RENDERER_H

#include <string>

#include "include/GLFW/glfw3.h" 

namespace gdh_engine {
	namespace manager {
		class Renderer {
		public:
			Renderer(const char* title, const unsigned int kMajorVersion, const unsigned int kMinorVersion,
				const unsigned int kWindowHeight, const unsigned int kWindowWidth);
			Renderer(std::string title, const unsigned int kMajorVersion, const unsigned int kMinorVersion,
				const unsigned int kWindowHeight, const unsigned int kWindowWidth);
			~Renderer();

			void ClearWindowToRender();
			void SwapBuffearsOnWindow();
			bool IsWindowShouldClose();

			GLFWwindow* get_engine_window() const
			{
				return engine_window_;
			}

			// it's callback function in openGL
			static void ResizeWindowFrameBuffer(GLFWwindow* window, int fbw, int fbh);

		private:
			const unsigned int kGlfwContextMajorVersion;
			const unsigned int kGlfwContextMinorVersion;

			size_t window_width_;
			size_t window_height_;

			std::string engine_window_title_;

			GLFWwindow* engine_window_;
		};
	} // namespace manager
} // namespace gdh_engine

#endif // GDH_ENGINE_RENDERER_H