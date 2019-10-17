#ifndef PHYSICS_H
#define PHYSICS_H
#include <glm/glm.hpp>
class Physics
{
private:
public:
	glm::vec3 gravity;
	Physics();
	glm::vec3 updatePos(glm::vec3 pos, glm::vec3 velocity);
	glm::vec3 updateVelocity(glm::vec3 velocity, glm::vec3 acceleration);
};


#endif