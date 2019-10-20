#include "force.h"
Gravity::Gravity(const glm::vec3& gravityIn)
{
	gravity=gravityIn;
}

Drag::Drag(float k, float m)
{
	k1=k;
	k2=m;
}

void Gravity::updateForce(Object* object, float duration)
{
	if (!object->hasFiniteMass()) return;
	glm::vec3 gForce = gravity * object->getMass();
	object->addForce(gForce);
}

void Drag::updateForce(Object* object, float duration)
{
	glm::vec3 force = object->getVelocity();
	float dragCoeff = (float)glm::length(force);
	dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;
	// Calculate the final force and apply it.
	//force = glm::normalize(force);
	force = force*(dragCoeff*-1);
	object->addForce(force);
}

void ForceRegisters::add(Object* object, ForceGenerator* fg)
{
	registrations.push_back(ForceRegistration(object,fg)); 
}

void ForceRegisters::updateForces(float duration)
{
	Registry::iterator i = registrations.begin();
	for (; i != registrations.end(); i++)
	{
		i->fg->updateForce(i->object, duration);
	}
}