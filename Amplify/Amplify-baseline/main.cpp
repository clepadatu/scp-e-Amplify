#include "private_libraries/window/window.h"
#include "private_libraries/input/input.h"
#include "private_libraries/maths/maths.h"
#include "private_libraries/utils/fileutils.h"
#include "private_libraries/graphics/shader.h"
#include "private_libraries/graphics/buffers/buffer.h"
#include "private_libraries/graphics/buffers/indexbuffer.h"
#include "private_libraries/graphics/buffers/vertexarray.h"


int main()
{	//====================================Namespace inclusion
	using namespace Erebos;
	using namespace graphics;
	using namespace maths;

	//=====================================Create Window 
	Window window("Erebos", 960, 540);
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
#if 0
	GLfloat vertices[] =
	{
		0, 0, 0,
		8, 0, 0,
		0, 3, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
#else

	GLfloat vertices[] =
	{
		0, 0, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0
	};

	GLushort indices[] =
	{
		0, 1, 2,
		2, 3, 0

	};

	GLfloat colorsA[]=
	{
		0.67,0.3,0.3,0.2,
		0.67, 0.3, 0.3, 0.2,
		0.67, 0.3, 0.3, 0.2,
		0.67, 0.3, 0.3, 0.2
	};

	GLfloat colorsB[] =
	{
		0.45f, 0.3f, 0.8f, 1.0f,
		0.45f, 0.3f, 0.8f, 1.0f,
		0.45f, 0.3f, 0.8f, 1.0f,
		0.45f, 0.3f, 0.8f, 1.0f
	};



	VertexArray sprite1,sprite2,sprite3;
	IndexBuffer ibo(indices, 6);

	sprite1.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	sprite1.addBuffer(new Buffer(colorsA, 4 * 4, 4), 1);

	sprite2.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	sprite2.addBuffer(new Buffer(colorsB, 4 * 4, 3), 1);
	
	sprite3.addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
	sprite3.addBuffer(new Buffer(colorsB, 4 * 4, 2), 1);

#endif
	mat4 ortho = mat4::ortographic(0.0f, 16.0f, 9.0f, 0.0f, -1.0f, 1.0f);

	Shader shader("private_libraries/shaders/basic.vert", "private_libraries/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));

	//shader.setUniform2f("light_position", vec2(4.0f, 1.5f));
	shader.setUniform4f("palette", vec4(0.45f, 0.3f, 0.8f, 1.0f));



	//semi-gameloop, window.closed based
	while (!window.closed())
		{

		//INPUTS


		//LOGIC


		//RENDER













		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		std::cout << "(X,Y):" << x << "," << y << std::endl;
		shader.setUniform2f("light_position", vec2((float)(x*16.0f / 960.0f), (float)(9.0f - y*9.0f / 540.0f)));
#if 0
		glDrawArrays(GL_TRIANGLES, 0, 6);
#else
		sprite1.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", mat4::translation(vec3(0, 0, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		sprite1.unbind();


		sprite2.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		sprite2.unbind();

		sprite3.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", mat4::translation(vec3(5, 6, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		sprite3.unbind();
#endif
		system("cls");
		window.update();
		

		}

	return 0;

}