#ifndef PHYSICS_H
#define PHYSICS_H
#include <glm/glm.hpp>
#include "object.h"

//static const glm::vec3 gravity = glm::vec3(0.0,-9.8,0.0);
class Physics
{
private:
	Physics();
public:
	static void update(Object* object);
};


#endif