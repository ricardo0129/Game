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

Spring::Spring(Object *o, float s, float r)
{
	other=o;
	springConstant=s;
	restLength=r;
}

AnchorSpring::AnchorSpring(glm::vec3* a, float s, float r)
{
	anchor=a;
	springConstant=s;
	restLength=r;
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
	if(dragCoeff!=0) force = glm::normalize(force);
	force = force*(dragCoeff*-1);
	object->addForce(force);
}

void Spring::updateForce(Object* object, float duration)
{
	glm::vec3 force=object->getPos();
	force -= other->getPos();
	float magnitude = glm::length(force);
	magnitude = (float)abs(magnitude - restLength);
	magnitude *= springConstant;
	if(glm::length(force)!=0) force=glm::normalize(force);
	force *= -magnitude;
	object->addForce(force);
}

void AnchorSpring::updateForce(Object* object, float duration)
{
	glm::vec3 force =object->getPos();
	force -= *anchor;
	float magnitude = glm::length(force);
	magnitude = (float)abs(magnitude - restLength);
	magnitude *= springConstant;
	if(glm::length(force)!=0) force=glm::normalize(force);
	force *= -magnitude;
	object->addForce(force);
}

void BungeeSpring::updateForce(Object* object, float duration)
{
	glm::vec3 force =object->getPos();
	force -= other->getPos();
	float magnitude = glm::length(force);
	if (magnitude <= restLength) return;
	magnitude = springConstant * (restLength - magnitude);
	if(glm::length(force)!=0) force=glm::normalize(force);
	force *= -magnitude;
	object->addForce(force);
}

void Boyancy::updateForce(Object* object, float duration)
{
	float depth = object->getPos().y;
	if (depth >= waterHeight + maxDepth) return;
	glm::vec3 force(0.0,0.0,0.0);
	if (depth <= waterHeight - maxDepth)
	{
	force.y = liquidDensity * volume;
	object->addForce(force);
	return;
	}
	// Otherwise we are partly submerged.
	force.y = liquidDensity * volume *
	(depth - maxDepth - waterHeight) / 2 * maxDepth;
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