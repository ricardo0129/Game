#include "object.h"
#include <iostream>
using namespace std;

Object::Object(float* verts, glm::vec3 position)
{
	vertices = verts;
	pos = position;
	glm::mat4 trans = glm::mat4(1.0f);
    model = glm::translate(trans, pos);
    velocity = glm::vec3(0.0f,0.0f,0.0f);
    acceleration = glm::vec3(0.0,0.0,0.0);
    totalForce = glm::vec3(0.0,0.0,0.0);
    mass=1.0f;
}

void Object::translate(glm::vec3 move)
{
	pos += move;
	glm::mat4 trans = glm::mat4(1.0f);
	model = glm::translate(trans, pos);
}

void Object::rotate(float ang)
{
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, pos);
	model = glm::rotate(trans, ang, glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::mat4 Object::getModel()
{
	return model;
}

glm::vec3 Object::getPos()
{
	return pos;
}

glm::vec3 Object::getVelocity()
{
	return velocity;
}

glm::vec3 Object::getAcceleration()
{
	return acceleration;
}

glm::vec3 Object::getTotalForce()
{
	return totalForce;
}

float Object::getMass()
{
	return mass;
}

void Object::setPos(glm::vec3 newPos)
{
	pos=newPos;
}

void Object::setVelocity(glm::vec3 newVelocity)
{
	velocity=newVelocity;
}

void Object::setAcceleration(glm::vec3 newAcceleration)
{
	acceleration=newAcceleration;
}

void Object::clearForce()
{
	totalForce=glm::vec3(0,0,0);
}

void Object::addForce(glm::vec3 &force)
{
	totalForce = totalForce + force;
}

bool Object::hasFiniteMass()
{
	return true;
}