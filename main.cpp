// Code adapted from www.learnopengl.com, www.glfw.org

#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_interpolation.hpp>
#include <glm/gtc/constants.hpp>

#include "shader.h"

int main(void)
{
	//create a glfw window
	GLFWwindow* window;

	if (!glfwInit()) //Initialize the library
		return -1;
	int wHeight = 960;
	int wWidth = 960;

	window = glfwCreateWindow(wWidth, wHeight, "OpenGL Window", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);//Make the window's context current

	//Initialize GLEW to setup the OpenGL Function pointers
	glewExperimental = GL_TRUE;
	glewInit();

	//Define the viewport dimensions
	glViewport(0, 0, 960, 960);

	//Set up vertex data (and buffer(s)) and attribute pointers

	//Large Right Angled Triangle 1 (in red)
	GLfloat triangle1[] = {
		-0.5, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, //bottom left
		-0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, //top left
		 0.0f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f  //middle
	};
	//Large Right Angled Triangle 2 (in green)
		GLfloat triangle2[] = {
		 -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f, //top left
		 0.0f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f, //middle
		 0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f  //top right

	};
	
	//Small Right Angled Triangle 1 (in blue)
	GLfloat triangle3[] = {
		0.5f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f, //top right
		0.5f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f, //bottom right
		0.25f, 0.25f, 0.0f,  0.0f, 0.0f, 1.0f  //middle
	};

	//Small Right Angled Triangle 2 (in turqoise)
	GLfloat triangle4[] = {
	    -0.25f, -0.25f, 0.0f,  0.0f, 1.0f, 1.0f, //bottom left
		0.25f,  -0.25f, 0.0f,  0.0f, 1.0f, 1.0f, //bottom right
		0.0f,   0.0f, 0.0f,   0.0f, 1.0f, 1.0f   //middle
	};

	//Medium Right Angled Triangle (in yellow)
	GLfloat triangle5[] = {
		0.0f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f, //bottom left
		0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f, //bottom right
		0.5f, 0.0f, 0.0f,  1.0f, 1.0f, 0.0f   //top right
	};

	//Square (in purple)
	GLfloat square1[] = {
		0.25f, 0.25f, 0.0f,  1.0f, 0.0f, 1.0f, //top
		0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 1.0f, //left
		0.25f, -0.25f, 0.0f,  1.0f, 0.0f, 1.0f, //bottom
		0.5f, 0.0f, 0.0f,  1.0f, 0.0f, 1.0f  //right
	};

	//Parallelogram (in orange)
	GLfloat parallelogram[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.65f, 0.0f, //bottom left
		-0.25f, -0.25, 0.0f,  1.0f, 0.65f, 0.0f, //top left
		0.0f, -0.5f, 0.0f,  1.0f, 0.65f, 0.0f, //bottom left
		0.25f, -0.25f, 0.0f,  1.0f, 0.65f, 0.0f  //bottom right
	};

	//I've done the vertices for all of the shapes.

	//Triangles 1-5 correspond with indices 1-5, indices 6 is the square, indices 7 is the parallelogram
	GLuint indices1[] = {
		0,1,2
	};

	GLuint indices2[] = {
		0,1,2
	};

	GLuint indices3[] = {
		0,1,2
	};

	GLuint indices4[] = {
		0,1,2
	};
	GLuint indices5[] = {
		0,1,2
	};

	GLuint indices6[] = {
		0,1,3,
		1,2,3,
	};

	GLuint indices7[] = {
		0,1,2,
		1,2,3,
	};

	//Create the Buffers & Vertes Arrays
	GLuint VBOs[7], VAOs[7], EBOs[7];
	glGenVertexArrays(7, VAOs);
	glGenBuffers(7, VBOs);
	glGenBuffers(7, EBOs);

	// ================================
	// buffer setup
	// ===============================

	//Triangle One
	glBindVertexArray(VAOs[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Triangle Two
	glBindVertexArray(VAOs[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle2), triangle2, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Triangle 3
	glBindVertexArray(VAOs[2]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle3), triangle3, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices3), indices3, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Triangle 4
	glBindVertexArray(VAOs[3]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle4), triangle4, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices4), indices4, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Triangle 5
	glBindVertexArray(VAOs[4]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle5), triangle5, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[4]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices5), indices5, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Square
	glBindVertexArray(VAOs[5]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square1), square1, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[5]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices6), indices6, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Parallelogram
	glBindVertexArray(VAOs[6]);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[6]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(parallelogram), parallelogram, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[6]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices7), indices7, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Bind all the vertex arrays
	glBindVertexArray(0);
	glBindVertexArray(1);
	glBindVertexArray(2);
	glBindVertexArray(3);
	glBindVertexArray(4);
	glBindVertexArray(5);
	glBindVertexArray(6);



	//Build and compile shader program
	GLuint shaderProgram = initShader("vert.glsl", "frag.glsl");

	//animating is set to true on mouse click, and then false when the animation is done
	bool animating = false;

	//sets the running time to 0
	glfwSetTime(0);

	//mvp matrix for zooming the camera out.
	glm::mat4 Projection = glm::perspective(45.0f, GLfloat(wWidth) / GLfloat(wHeight), 0.1f, 100.0f);
	glm::mat4 View = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 2.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
	glm::mat4 VP = Projection * View;


	// Loop until the user closes the window 
	while (!glfwWindowShouldClose(window))
	{
		// Render here 
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw the first Triangle
		// use shader
		glUseProgram(shaderProgram);

		// Define transform matrix
		glm::mat4 transform;

		//if the mouse is clicked, the animation begins and time is reset.
		if (glfwGetMouseButton(window,0) == GLFW_PRESS) {
			animating = true;
			glfwSetTime(0);
		}

		//anim_time is the time the animation should run for in seconds.
		float anim_time = 3.5f;

		//anim_fraction is the fraction of the animation that is done.
		float anim_fraction = 0.0f;

		//if it's animating
		if (animating){

			//if its been animating for less time than the animation time
			if (glfwGetTime() < anim_time) {

				//set a new anim_fraction
				anim_fraction = glfwGetTime() / anim_time;
			} else {

				//else, it is done animating
				anim_fraction = 1.0f;
			}
		}

		// Get matrix's uniform location and set matrix

		GLint transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		// draw objects
		//red triangle

		//Translations
		transform = glm::translate(transform, glm::vec3((0.75f * anim_fraction), (0.0f * anim_fraction), (0.0f*anim_fraction))); //translate
		transform = glm::rotate(transform, glm::radians(-45.0f * anim_fraction), glm::vec3(0.0f, 0.0f, -1.0f));					 //rotate
		transform = VP * transform;																								 //scale
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, GLint((sizeof(triangle1) / sizeof(GLfloat)) / 3));

		//green triangle
		transform = glm::mat4(1.0);
		transform = glm::translate(transform, glm::vec3((-0.31f*anim_fraction), (-0.355f * anim_fraction), (0.0f *anim_fraction)));
		transform = glm::rotate(transform, glm::radians(45.0f * anim_fraction), glm::vec3(0.0f, 0.0f, -1.0f));
		transform = VP * transform;
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, GLint((sizeof(triangle2) / sizeof(GLfloat)) / 3));

		//small blue triangle
		transform = glm::mat4(1.0);
		transform = glm::translate(transform, glm::vec3((0.4f * anim_fraction), (-1.065f * anim_fraction), (0.0f * anim_fraction)));
		transform = glm::rotate(transform, glm::radians(-45.0f * anim_fraction), glm::vec3(0.0f, 0.0f, -1.0f));
		transform = VP * transform;
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glBindVertexArray(VAOs[2]);
		glDrawArrays(GL_TRIANGLES, 0, GLint((sizeof(triangle3) / sizeof(GLfloat)) / 3));

		//turqoise triangle
		transform = glm::mat4(1.0);
		transform = glm::translate(transform, glm::vec3((0.75f * anim_fraction), (0.35f * anim_fraction), (0.0f * anim_fraction)));
		transform = glm::rotate(transform, glm::radians(-45.0f * anim_fraction), glm::vec3(0.0f, 0.0f, -1.0f));
		transform = VP * transform;
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glBindVertexArray(VAOs[3]);
		glDrawArrays(GL_TRIANGLES, 0, GLint((sizeof(triangle4) / sizeof(GLfloat)) / 3));

		//yellow triangle
		transform = glm::mat4(1.0);
		transform = glm::translate(transform, glm::vec3((-0.6625f * anim_fraction), (-0.2f * anim_fraction), (0.0f * anim_fraction)));
		transform = glm::rotate(transform, glm::radians(225.0f * anim_fraction), glm::vec3(0.0f, 0.0f, -1.0f));
		transform = VP * transform;
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glBindVertexArray(VAOs[4]);
		glDrawArrays(GL_TRIANGLES, 0, GLint((sizeof(triangle5) / sizeof(GLfloat)) / 3));

		//square
		transform = glm::mat4(1.0);
		transform = glm::translate(transform, glm::vec3((-0.31f * anim_fraction), (-0.355f * anim_fraction), (0.0f * anim_fraction)));
		transform = glm::rotate(transform, glm::radians(45.0f * anim_fraction), glm::vec3(0.0f, 0.0f, -1.0f));
		transform = VP * transform;
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glBindVertexArray(VAOs[5]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//parallelogram
		transform = glm::mat4(1.0);
		transform = glm::translate(transform, glm::vec3((-0.662f * anim_fraction), (0.155f * anim_fraction), (0.0f * anim_fraction)));
		transform = glm::rotate(transform, glm::radians(180.0f * anim_fraction), glm::vec3(-1.0f, 0.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(-45.0f * anim_fraction), glm::vec3(0.0f, 0.0f, -1.0f));
		transform = VP * transform;
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glBindVertexArray(VAOs[6]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(7, VAOs);
	glDeleteBuffers(7, VBOs);

	glfwTerminate();
	return 0;
}