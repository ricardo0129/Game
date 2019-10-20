#include "projectile.h"

Projectile::Projectile(float* verts, glm::vec3 position):Object(verts,position)
{
	
}

bool Firework::update(float time)
{
	Physics::update(this);
	age-=time;
	return (age<0);
}

