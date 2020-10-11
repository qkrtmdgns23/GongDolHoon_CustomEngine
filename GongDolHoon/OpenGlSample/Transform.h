#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

typedef struct object_transform_information
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
}obj_transform_t;

class Shader;

class Transform
{
public:
	Transform(obj_transform_t transform_inform = {glm::vec3(0), glm::vec3(0), glm::vec3(0)});
	
	// property::set
	void set_position(const glm::vec3 position);
	void set_rotation(const glm::vec3 rotation);
	void set_scale(const glm::vec3 scale);

	// method
	void move(const glm::vec3 position);
	void rotate(const glm::vec3 rotation);
	void resize(const glm::vec3 scale);

	// property::get
	glm::mat4 get_model_matrix() const;
	
	void update_uniforms(Shader* vertex_shader);

private:
	// this function called in move, rotate, resize, setter
	void update_model_matrix();

	glm::vec3 obj_origin_;
	glm::vec3 obj_position_;
	glm::vec3 obj_rotation_;
	glm::vec3 obj_scale_;

	glm::mat4 model_matrix_;
};

#endif /* TRANSFORM_H */
