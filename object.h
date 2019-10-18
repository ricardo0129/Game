#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Object
{
private:
	glm::vec3 pos;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	glm::mat4 model;
	float mass;
	float* vertices;
	float angle;
public:
	Object(float* verts, glm::vec3 position);
	void translate(glm::vec3 move);
	glm::vec3 getPos();
	glm::vec3 getVelocity();
	glm::vec3 getAcceleration();
	void setPos(glm::vec3 newPos);
	void setVelocity(glm::vec3 newVelocity);
	void setAcceleration(glm::vec3 newAcceleration);
	float getMass();
	void rotate(float angle);
	glm::mat4 getModel();
};


#endif