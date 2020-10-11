#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 world_ceiling)
{
	this->view_matrix_ = glm::mat4(1.0f);

	this->world_ceiling_ = world_ceiling;
	this->position_ = position;
	this->right_ = glm::vec3(0.f);
	this->up_ = world_ceiling;

	update_camera();
}

Camera::~Camera()
{

}

void Camera::update_camera()
{
	this->front_ = glm::normalize(this->front_);
	this->right_ = glm::normalize(this->right_);
	this->up_ = glm::normalize(this->up_);

}

const glm::mat4 Camera::get_view_matrix()
{
	this->update_camera();
	this->view_matrix_ = glm::lookAt(this->position_, glm::vec3(0.f, 0.f, 0.f), this->up_);
	
	return this->view_matrix_;
}

const glm::vec3 Camera::get_cam_pos()
{
	return this->position_;
}