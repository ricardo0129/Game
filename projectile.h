#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "object.h"
#include <glm/glm.hpp>
class Projectile : public Object
{
private:
public:
	Projectile(float* verts, glm::vec3 position);

};
//note e=ms^2| e=energy, m=mass, s=speed
class Payload :public Projectile
{
private:
public:
	unsigned type;
	unsigned count;
}
class Firework : public Projectile
{
private:
public:
	unsigned type;
	float minAge;
	float maxAge;
	glm::vec3 minVelocity;
	glm::vec3 maxVelocity;
	unsigned payLoadCount;
	Payload *payloads;
};
#endif