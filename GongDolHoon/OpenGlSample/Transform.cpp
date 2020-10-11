#include "Transform.h"
#include "Shader.h"

Transform::Transform(obj_transform_t transform_inform)
{
	this->obj_origin_ = glm::vec3(0.0f);
	this->obj_position_ = transform_inform.position;
	this->obj_rotation_ = transform_inform.rotation;
	this->obj_scale_ = transform_inform.scale;

	update_model_matrix();
}

void Transform::set_position(const glm::vec3 position)
{
	this->obj_position_ = position;
	update_model_matrix();
}

void Transform::set_rotation(const glm::vec3 rotation)
{
	this->obj_rotation_ = rotation;
	update_model_matrix();
}

void Transform::set_scale(const glm::vec3 scale)
{
	this->obj_scale_ = scale;
	update_model_matrix();
}

void Transform::move(const glm::vec3 position)
{
	this->obj_position_ += position;
	update_model_matrix();
}

void Transform::rotate(const glm::vec3 rotation)
{
	this->obj_rotation_ += rotation;
	update_model_matrix();
}

void Transform::resize(const glm::vec3 scale)
{
	this->obj_scale_ += scale;
	update_model_matrix();
}

glm::mat4 Transform::get_model_matrix() const
{
	return this->model_matrix_;
}

void Transform::update_uniforms(Shader* vertex_shader)
{
	update_model_matrix();
	vertex_shader->set_mat4("Model", model_matrix_);
}

void Transform::update_model_matrix()
{
	this->model_matrix_ = glm::mat4(1.f);
	this->model_matrix_ = glm::translate(this->model_matrix_, this->obj_origin_);
	this->model_matrix_ = glm::rotate(this->model_matrix_, glm::radians(this->obj_rotation_.x), glm::vec3(1.f, 0.f, 0.f));
	this->model_matrix_ = glm::rotate(this->model_matrix_, glm::radians(this->obj_rotation_.y), glm::vec3(0.f, 1.f, 1.f));
	this->model_matrix_ = glm::rotate(this->model_matrix_, glm::radians(this->obj_rotation_.z), glm::vec3(0.f, 0.f, 1.f));
	this->model_matrix_ = glm::translate(this->model_matrix_, this->obj_position_ - this->obj_origin_);
	this->model_matrix_ = glm::scale(this->model_matrix_, this->obj_scale_);
}