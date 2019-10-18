#ifndef PHYSICS_H
#define PHYSICS_H
#include <glm/glm.hpp>
#include "object.h"

class Physics
{
private:
public:
	glm::vec3 gravity;
	Physics();
	void update(Object* object, glm::vec3 foce);
};


#endif