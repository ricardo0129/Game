#include "object.h"
#include <iostream>
using namespace std;

Object::Object(float* verts, glm::vec3 position)
{
	vertices = verts;
	pos = position;
	glm::mat4 trans = glm::mat4(1.0f);
    model = glm::translate(trans, pos);
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