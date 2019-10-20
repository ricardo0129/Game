#include "physics.h"

Physics::Physics()
{
	//gravity  = glm::vec3(0.0,-9.8,0.0); 
}

void Physics::update(Object* object)
{
	glm::vec3 position = object->getPos() + object->getVelocity()*(1.0f/60.0f);
	glm::vec3 acceleration = object->getTotalForce() / object->getMass();
	glm::vec3 velocity = object->getVelocity()*0.995f + acceleration * (1.0f/60.0f);
	object->setPos(position);
	object->setVelocity(velocity);
	object->setAcceleration(acceleration);
}


 