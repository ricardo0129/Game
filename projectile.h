#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "object.h"
#include "physics.h"
#include <glm/glm.hpp>
class Projectile : public Object
{
private:
public:
	Projectile(float* verts, glm::vec3 position);
	void update();
};
//note e=ms^2| e=energy, m=mass, s=speed
class Payload :public Projectile
{
private:
public:
	unsigned type;
	unsigned count;
};
class Firework : public Projectile
{
private:
	unsigned type;
	float minAge;
	float maxAge;
	float age;
	glm::vec3 minVelocity;
	glm::vec3 maxVelocity;
	unsigned payLoadCount;
	Payload *payloads;
public:
	void create(Firework* firework, const Firework* parent=NULL)const;
	bool update(float time);
};
#endif