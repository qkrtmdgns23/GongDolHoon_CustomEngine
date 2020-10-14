#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace gdh_engine {
	namespace object {
		typedef struct ObjectTransformInformation
		{
			glm::vec3 position;
			glm::vec3 rotation;
			glm::vec3 scale;
		}obj_transform_t;

		class Object;

		class Transform
		{
		public:
			Transform(obj_transform_t transform_inform = { glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f) });

			// method
			void Move(const glm::vec3 position);
			void Rotate(const glm::vec3 rotation);
			void Resize(const glm::vec3 scale);

			void set_position(const glm::vec3 position)
			{
				this->obj_position_ = position;
			}
			void set_rotation(const glm::vec3 rotation)
			{
				this->obj_rotation_ = rotation;
			}
			void set_scale(const glm::vec3 scale)
			{
				this->obj_scale_ = scale;
			}
			void set_model_matrix(glm::mat4 model)
			{
				model_matrix_ = model;
			}

			glm::mat4 get_model_matrix()
			{
				UpdateModelMatrix();
				return this->model_matrix_;
			}
			

		private:
			// this function called in move, rotate, resize, setter
			void UpdateModelMatrix();

			glm::vec3 obj_origin_;
			glm::vec3 obj_position_;
			glm::vec3 obj_rotation_;
			glm::vec3 obj_scale_;

			glm::mat4 model_matrix_;
		};
	} // namespace object
} // namespace gdh_engine

#endif /* TRANSFORM_H */
