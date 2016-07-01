#version 400 core

layout (location =0) in vec3 position;
layout (location =1) in vec4 color;

/*uniform mat4 pr_matrix;
uniform mat4 vw_matrix;
uniform mat4 ml_matrix;*/



uniform mat4 MVP;
uniform mat4 rotate;

//
out DATA
{

vec4 color;
} vs_out;


void main()
{
	
	gl_Position = vec4(position,1);
	//



	
	vs_out.color=color;
}