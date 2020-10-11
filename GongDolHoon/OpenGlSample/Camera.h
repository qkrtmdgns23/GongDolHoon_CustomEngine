#ifndef CAMERA_H
#define CAMERA_H

#include "include/GL/glew.h"		
#include "include/GLFW/glfw3.h" 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

typedef struct camera_data
{
	glm::vec3 world_ceiling;
	glm::vec3 camera_position;
}cam_data_t;

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 world_ceiling);
	~Camera();

	void update_camera();

	const glm::mat4 get_view_matrix();

	// this constant attribute can modify in the future.
	const glm::vec3 get_cam_pos();

private:
	glm::mat4 view_matrix_;

	glm::vec3 world_ceiling_;
	glm::vec3 position_;
	glm::vec3 front_;
	glm::vec3 right_;
	glm::vec3 up_;

};

#endif /* CAMERA_H */