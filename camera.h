#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Camera
{
private:
	glm::mat4 projection;
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
public:
	Camera(const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT);
	glm::mat4 getProjection();
	glm::mat4 getView(float yaw, float pitch);


};





#endif