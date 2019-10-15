#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Object
{
private:
	glm::vec3 pos;
	glm::mat4 model;
	float* vertices;
	float angle;
public:
	Object(float* verts, glm::vec3 position);
	void translate(glm::vec3 move);
	void rotate(float angle);
	glm::mat4 getModel();
};


#endif