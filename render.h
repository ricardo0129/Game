#ifndef RENDER_H
#define RENDER_H
#include <glad/glad.h>
class Render
{
private:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	unsigned int triangles;
public:
	int triangleCount;
	Render(float* vertices, int verticesCount);
	Render(float* vertices, int verticesCount, unsigned int ineces[], int indexCount);
	void draw();
	void drawElements();
	void bind();
};



#endif