#include "physics.h"

Physics::Physics()
{
	gravity  = glm::vec3(0.0,-9.8,0.0); 
}

void Physics::update(Object* object, glm::vec3 force)
{
	force = force + gravity;
	glm::vec3 last_acceleration = object->getAcceleration();
	glm::vec3 position = object->getPos() + object->getVelocity() * 1.0f/60.0f + ( 0.5f * last_acceleration * (1.0f/60.0f)*(1.0f/60.0f) );
	glm::vec3 new_acceleration = force / object->getMass();
	glm::vec3 avg_acceleration = ( last_acceleration + new_acceleration ) / 0.5f;
	glm::vec3 velocity = object->getVelocity()*0.995f + avg_acceleration * (1.0f/60.0f);
	object->setPos(position);
	object->setVelocity(velocity);
	object->setAcceleration(new_acceleration);
}


 