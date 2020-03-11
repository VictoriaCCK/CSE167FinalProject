#include "Window.h"

/* 
 * Declare your variables below. Unnamed namespace is used here to avoid 
 * declaring global or static variables.
 */
namespace
{
	int width, height;
	std::string windowTitle("GLFW Starter Project");

	Cube* cube;
	Creature* guider;
	Object* currentObj;  // The object currently displaying.

	glm::vec3 eye(0, 0, 20); // Camera position.
	glm::vec3 center(0, 0, 0); // The point we are looking at.
	glm::vec3 up(0, 1, 0); // The up direction of the camera.
	float fovy = 60;
	float near = 1;
	float far = 1000;
	glm::mat4 view = glm::lookAt(eye, center, up); // View matrix, defined by eye, center and up.
	glm::mat4 projection; // Projection matrix.

	GLuint program; // The shader program id.
	GLuint projectionLoc; // Location of projection in shader.
	GLuint viewLoc; // Location of view in shader.
	GLuint modelLoc; // Location of model in shader.
	GLuint colorLoc; // Location of color in shader.
    
    
    GLuint programGuider; // The shader program id.
    GLuint projectionLocGuider; // Location of projection in shader.
    GLuint viewLocGuider; // Location of view in shader.
    GLuint modelLocGuider; // Location of model in shader.
    GLuint colorLocGuider; // Location of color in shader.
    GLuint eyeLocGuider;
    GLuint specularLocGuider;
    GLuint diffuseLocGuider;
    GLuint ambientLocGuider;
};

bool Window::initializeProgram()
{
//    // Create a shader program with a vertex shader and a fragment shader.
//    program = LoadShaders("shaders/shader.vert", "shaders/shader.frag");
//
//    // Check the shader program.
//    if (!program)
//    {
//        std::cerr << "Failed to initialize shader program" << std::endl;
//        return false;
//    }
//
//    // Activate the shader program.
//    glUseProgram(program);
//    // Get the locations of uniform variables.
//    projectionLoc = glGetUniformLocation(program, "projection");
//    viewLoc = glGetUniformLocation(program, "view");
//    modelLoc = glGetUniformLocation(program, "model");
//    colorLoc = glGetUniformLocation(program, "color");

    if(initialGuider() == false) return false;
	return true;
}

bool Window::initializeObjects()
{
	// Create a cube of size 5.
	cube = new Cube(5.0f);

	return true;
}

void Window::cleanUp()
{
	// Deallcoate the objects.
	delete cube;
    delete guider;
	// Delete the shader program.
	glDeleteProgram(program);
    glDeleteProgram(programGuider);
}

GLFWwindow* Window::createWindow(int width, int height)
{
	// Initialize GLFW.
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return NULL;
	}

	// 4x antialiasing.
	glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__ 
	// Apple implements its own version of OpenGL and requires special treatments
	// to make it uses modern OpenGL.

	// Ensure that minimum OpenGL version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Enable forward compatibility and allow a modern OpenGL context
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create the GLFW window.
	GLFWwindow* window = glfwCreateWindow(width, height, windowTitle.c_str(), NULL, NULL);

	// Check if the window could not be created.
	if (!window)
	{
		std::cerr << "Failed to open GLFW window." << std::endl;
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window.
	glfwMakeContextCurrent(window);

#ifndef __APPLE__
	// On Windows and Linux, we need GLEW to provide modern OpenGL functionality.

	// Initialize GLEW.
	if (glewInit())
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return NULL;
	}
#endif

	// Set swap interval to 1.
	glfwSwapInterval(0);

	// Call the resize callback to make sure things get drawn immediately.
	Window::resizeCallback(window, width, height);

	return window;
}

void Window::resizeCallback(GLFWwindow* window, int w, int h)
{
#ifdef __APPLE__
	// In case your Mac has a retina display.
	glfwGetFramebufferSize(window, &width, &height);
#endif
	width = w;
	height = h;
	// Set the viewport size.
	glViewport(0, 0, width, height);

	// Set the projection matrix.
	projection = glm::perspective(glm::radians(fovy),
		(float)width / (float)height, near, far);
}

void Window::idleCallback()
{
	// Perform any updates as necessary. 
//    currentObj->update();
}

void Window::displayCallback(GLFWwindow* window)
{
    displayGuider(window);
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	/*
	 * TODO: Modify below to add your key callbacks.
	 */

	 // Check for a key press.
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		case GLFW_KEY_1:
			// Set currentObj to cube
			currentObj = cube;
			break;
		default:
			break;
		}
	}
}

bool Window::initialGuider()
{
    programGuider = LoadShaders("shaders/toon shader.vert", "shaders/toon shader.frag");
    
    // Check the shader program.
    if (!programGuider)
    {
        std::cerr << "Failed to initialize shader program" << std::endl;
        return false;
    }
    
    // Activate the shader program.
    glUseProgram(program);
    // Get the locations of uniform variables.
    projectionLocGuider = glGetUniformLocation(programGuider, "projection");
    viewLocGuider = glGetUniformLocation(programGuider, "view");
    modelLocGuider = glGetUniformLocation(programGuider, "model");
    colorLocGuider = glGetUniformLocation(programGuider, "color");
    eyeLocGuider = glGetUniformLocation(programGuider, "eye");
    specularLocGuider = glGetUniformLocation(programGuider, "specular");
    ambientLocGuider = glGetUniformLocation(programGuider, "ambient");
    diffuseLocGuider = glGetUniformLocation(programGuider, "diffuse");
    
    guider = new Creature("/Users/victoria/Downloads/Avatar.obj", 3);
    return true;
}

void Window::displayGuider(GLFWwindow* window)
{
    // Switch back to using OpenGL's rasterizer
    glUseProgram(programGuider);
    // Clear the color and depth buffers.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Specify the values of the uniform variables we are going to use.
    /*
     * TODO: Section 3 and 4: Modify the code here to draw both the bunny and
     * the dragon
     * Note that the model matrix sent to the shader belongs only
     * to what object the currentObj ptr is pointing to. You will need to
     * use another call to glUniformMatrix4fv to change the model matrix
     * data being sent to the vertex shader before you draw the other object
     */
    glm::mat4 model = guider->getModel();
    glm::vec3 color = guider->getColor();
    glUniformMatrix4fv(projectionLocGuider, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(viewLocGuider, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(modelLocGuider, 1, GL_FALSE, glm::value_ptr(model));
    glUniform3fv(colorLocGuider, 1, glm::value_ptr(color));
    glUniform3fv(eyeLocGuider, 1, glm::value_ptr(eye));
    glUniform3fv(ambientLocGuider, 1, glm::value_ptr(guider->ambient));
    glUniform3fv(specularLocGuider, 1, glm::value_ptr(guider->specular));
    glUniform3fv(diffuseLocGuider, 1, glm::value_ptr(guider->diffuse));
    // Render the object.
    guider->draw();
    
    // Gets events, including input such as keyboard and mouse or window resizing.
    glfwPollEvents();
    // Swap buffers.
    glfwSwapBuffers(window);
}
