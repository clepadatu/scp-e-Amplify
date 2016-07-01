#include "private_libraries/window/window.h"
#include "private_libraries/input/input.h"
#include "private_libraries/maths/maths.h"
#include "private_libraries/utils/fileutils.h"
#include "private_libraries/graphics/shader.h"
#include "private_libraries/graphics/buffers/buffer.h"
#include "private_libraries/graphics/buffers/indexbuffer.h"
#include "private_libraries/graphics/buffers/vertexarray.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>




int main()
{	//====================================Namespace inclusion
	using namespace Erebos;
	using namespace graphics;
	using namespace maths;

	//=====================================Create Window 

	Window* window = new Window("Amplify", 1024, 768);

	window->WindowColor(0.0f, 0.0f, 0.0f, 0.3f);


	GLfloat vertices[] =
	{
		-1.0f, -1.0f, 0.0f,0.0f,
		1.0f, -1.0f, 0.0f,0.0f,
		0.0f, 1.0f, 0.0f,0.0f
	};

	GLushort indices[] =
	{
		0, 1, 2
		

	};

	GLfloat colorsA[] =
	{
		0.67f, 0.3f, 0.3f, 0.2f,
		0.67f, 0.3f, 0.3f, 0.2f,
		0.67f, 0.3f, 0.3f, 0.2f
		
	};

	GLfloat colorsB[] =
	{
		1.0f, 0.0f, 0.0f, 1,
		1.0f, 0.0f, 0.0f, 1,
		1.0f, 0.0f, 0.0f, 1
		
	};



	VertexArray sprite1;
	IndexBuffer ibo(indices, 3);

	sprite1.addBuffer(new Buffer(vertices, 4 * 3, 4), 0);
	sprite1.addBuffer(new Buffer(colorsB, 4 * 3, 4), 1);




	


	Shader shader("private_libraries/shaders/basic.vert", "private_libraries/shaders/basic.frag");
	shader.enable();
	
	mat4 rotate = mat4::rotation(180.0f, vec3::vec3(0.0f, 0.0f, 0.1f));

	mat4 projection_matrix = mat4::perspective(30.0f, 1024.0f / 768.0f, 1.0f, 10.0f);
	// Camera matrix
	mat4 view_matrix = mat4::lookAt(
		vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		vec3(0, 0, 0), // and looks at the origin
		vec3(0, 0, 1)  // Head is up (set to 0,-1,0 to look upside-down)
		);
	mat4 model_matrix = mat4::identity();


	mat4 MVP = projection_matrix * view_matrix*model_matrix;

	shader.setUniformMat4("MVP", MVP);
	shader.setUniformMat4("rotation", MVP);
	for (int i = 0; i <= 15; i++)
		std::cout << "M" << i << "= " << MVP.elements[i] << std::endl;
	
	/*shader.setUniformMat4("pr_matrix", proj);
	shader.setUniformMat4("ml_matrix", mat4::identity());
	shader.setUniformMat4("vw_matrix", vw_matrix);
	*/






	//semi-gameloop, window.closed based
	while (!window->closed())
	{

		//INPUTS
		double x, y;
		window->getMousePosition(x, y);
		//std::cout << "(X,Y):" << x << "," << y << std::endl;

	
		//LOGIC
		

		//RENDER
		window->clear();

		
		sprite1.bind();
		ibo.bind();
		//shader.setUniformMat4("ml_matrix", t1);
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		sprite1.unbind();
		
	

		window->update();
	}

	window->~Window();
	return 0;

}