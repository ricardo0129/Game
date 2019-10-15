#ifndef RENDER_H
#define RENDER_H
#include <glad/glad.h>
class Render
{
private:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
public:
	int triangleCount;
	Render(float* vertices, int verticesCount,int vertexCount);
	void draw();
	void bind();
};



#endif