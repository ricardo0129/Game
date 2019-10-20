#ifndef FORCE_H
#define FORCE_H
#include <vector>
#include "object.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class ForceGenerator
{
public:
	virtual void updateForce(Object* object, float duration) = 0;
};

class Gravity : public ForceGenerator
{
glm::vec3 gravity;
public:
	Gravity(const glm::vec3& gravityIn);
	virtual void updateForce(Object* object, float duration);
};

class Drag : public ForceGenerator
{
	float k1;
	float k2;
public:
	Drag(float k, float m);
	virtual void updateForce(Object* object, float duration);

};

/**
* Holds all the force generators and the particles they apply to.
*/
class ForceRegisters
{
protected:
	struct ForceRegistration
	{
	Object *object;
	ForceGenerator *fg;
	ForceRegistration(Object* rObject, ForceGenerator* cFg)
	{
		object=rObject;
		fg=cFg;
	}
	};
	typedef std::vector<ForceRegistration> Registry;
	Registry registrations;
public:
	void add(Object* object, ForceGenerator* fg);
	void remove(Object* object, ForceGenerator* fg);
	void clear();
	void updateForces(float duration);
};



#endif