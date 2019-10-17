#include "physics.h"

Physics::Physics()
{
	gravity  = glm::vec3(0.0,-9.8,0.0); 
}

glm::vec3 Physics::updatePos(glm::vec3 pos, glm::vec3 velocity)
{
	return pos + velocity;
}

glm::vec3 Physics::updateVelocity(glm::vec3 velocity, glm::vec3 acceleration)
{
	return velocity + acceleration;
}