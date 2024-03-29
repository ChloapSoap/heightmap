/*
	Project 1 Submission for CMPSC458
    Name: Chloe Gregory
	psu id: ceg5409
*/

#include <Project1.hpp>

// globals 
	// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

	// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

	// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

	//input related
float xSpeed = 0.0f, ySpeed = 0.0f, zSpeed = 0.0f;
float xSize = 1.0f, ySize = 1.0f, zSize = 1.0f;
float xRotation = 0.0f, yRotation = 0.0f, zRotation = 0.0f;
glm::vec3 cubeInit[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};


std::string preamble =
"Project 1 code \n\n"
"Press the U,I,O to increase transformations \n"
"Press the J,K,L to decrease transformations \n"
"\tKey alone will alter rotation rate\n "
"\tShift+Key will alter scale\n "
"\tControl+Key will alter translation\n "
"Pressing G will reset transformations\n ";

int main(int argc, char **argv)
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X (left here as legacy, more would need to change)
	#endif

	 // Print Preamble
	std:printf(preamble.c_str());

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Project 1: Heightmap", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	// Set the required callback functions
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);


	// build and compile our shader program (defined in shader.hpp)
	// ------------------------------------
	Shader ourShader("../Project_1/Shaders/shader.vert", "../Project_1/Shaders/shader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes for boxes
	// ------------------------------------------------------------------

	//   3D Coordinates   | Texture Coordinates
	//    x     y     z   |  s     t  
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};


	//  1.  Create ID / Generate Buffers and for Vertex Buffer Object (VBO), 
	//      Vertex Array Buffer (VAO), and the Element Buffer Objects (EBO)
	unsigned int VBO, VAO, EBO;

	// 2. Bind Vertex Array Object
	glGenVertexArrays(1, &VAO);

	//  Bind the Vertex Buffer
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	
	// 3. Copy our vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 4. Copy our indices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 5.  Position attribute for the 3D Position Coordinates and link to position 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 6.  TexCoord attribute for the 2d Texture Coordinates and link to position 2
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	unsigned int box_texture = loadTexture("../Project_1/Media/textures/container.jpg");
	unsigned int smile_texture = loadTexture("../Project_1/Media/textures/awesomeface.png");
	unsigned int front_texture = loadTexture("../Project_1/Media/skybox/front.jpg");
	unsigned int back_texture = loadTexture("../Project_1/Media/skybox/back.jpg");
	unsigned int bottom_texture = loadTexture("../Project_1/Media/skybox/bottom.jpg");
	unsigned int left_texture = loadTexture("../Project_1/Media/skybox/left.jpg");
	unsigned int right_texture = loadTexture("../Project_1/Media/skybox/right.jpg");
	unsigned int top_texture = loadTexture("../Project_1/Media/skybox/top.jpg");


	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
					 // either set it manually like so:
	//Setting it using the texture class
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);

	// init heightmap (defined in heightmap.hpp)
	Heightmap heightmap("../Project_1/Media/heightmaps/hflab4.jpg");
	
	

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window, cubePositions);

		// render
		// ------
		// Set background color (shouldn't need it in the end b/c the box should fully cover everything
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// bind textures on corresponding texture units in fragment shader
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, box_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, smile_texture);

		// activate shader
		ourShader.use();

		// pass projection matrix to shader (note that in this case it could change every frame)
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);

		// camera/view transformation
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("view", view);

		
		// render boxes
		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model;
			// Translate the model to the cube starting position
			model = glm::translate(model, cubePositions[i]);
			// Rotate the cube by an angle
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(xRotation), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, glm::radians(yRotation), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(zRotation), glm::vec3(0.0f, 0.0f, 1.0f));

			model = glm::scale(model, glm::vec3(xSize, ySize, zSize));

			// Set model in shader
			ourShader.setMat4("model", model);

			// Draw the box with triangles
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		xRotation += xSpeed;
		yRotation += ySpeed;
		zRotation += zSpeed;

		// Bind new textures to boh texture positions (do both since it has 2 textures in the vertex shader)
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, front_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, front_texture);

		// Make the model for one wall and shift/scale it
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f) + camera.Position);
		model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));

		// Set model in shader
		ourShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		//draw back wall
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, back_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, back_texture);
		glm::mat4 modelBack;
		modelBack = glm::translate(modelBack, glm::vec3(0.0f, 0.0f, 0.0f) + camera.Position);
		modelBack = glm::scale(modelBack, glm::vec3(100.0f, 100.0f, 100.0f));
		modelBack = glm::rotate(modelBack, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		ourShader.setMat4("model", modelBack);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//draw bottom wall
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, bottom_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, bottom_texture);
		glm::mat4 modelBottom;
		modelBottom = glm::translate(modelBottom, glm::vec3(0.0f, 0.0f, 0.0f) + camera.Position);
		modelBottom = glm::scale(modelBottom, glm::vec3(100.0f, 100.0f, 100.0f));
		modelBottom = glm::rotate(modelBottom, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		modelBottom = glm::rotate(modelBottom, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		ourShader.setMat4("model", modelBottom);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//draw left wall
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, left_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, left_texture);
		glm::mat4 modelLeft;
		modelLeft = glm::translate(modelLeft, glm::vec3(0.0f, 0.0f, 0.0f) + camera.Position);
		modelLeft = glm::scale(modelLeft, glm::vec3(100.0f, 100.0f, 100.0f));
		modelLeft = glm::rotate(modelLeft, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		ourShader.setMat4("model", modelLeft);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//draw right wall
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, right_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, right_texture);
		glm::mat4 modelRight;
		modelRight = glm::translate(modelRight, glm::vec3(0.0f, 0.0f, 0.0f) + camera.Position);
		modelRight = glm::scale(modelRight, glm::vec3(100.0f, 100.0f, 100.0f));
		modelRight = glm::rotate(modelRight, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		ourShader.setMat4("model", modelRight);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//draw top wall
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, top_texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, top_texture);
		glm::mat4 modelTop;
		modelTop = glm::translate(modelTop, glm::vec3(0.0f, 0.0f, 0.0f) + camera.Position);
		modelTop = glm::scale(modelTop, glm::vec3(100.0f, 100.0f, 100.0f));
		modelTop = glm::rotate(modelTop, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		modelTop = glm::rotate(modelTop, glm::radians(270.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		ourShader.setMat4("model", modelTop);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Draw the heightmap (defined in heightmap.hpp)  Similar to above but you have to write it.
		heightmap.Draw(ourShader, bottom_texture);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, glm::vec3 cubePositions[])
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);

	// Add other key operations here.  
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			//increase the scale in x-axis
			xSize += 0.1f;
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {
			//positive translation in x-axis
			for (int i = 0; i < 10; i++) {
				cubePositions[i].x += 0.1f;
			}
		}
		else {
			//increase rotation rate in x-axis
			xSpeed += 0.05f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			//decrease the scale in x-axis
			xSize -= 0.1f;
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {
			//negative translation in x-axis
			for (int i = 0; i < 10; i++) {
				cubePositions[i].x -= 0.1f;
			}
		}
		else {
			//decrease rotation rate in x-axis
			xSpeed -= 0.05f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			//increase the scale in y-axis
			ySize += 0.1f;
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {
			//positive translation in y-axis
			for (int i = 0; i < 10; i++) {
				cubePositions[i].y += 0.1f;
			}
		}
		else {
			//increase rotation rate in y-axis
			ySpeed += 0.05f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			//decrease the scale in y-axis
			ySize -= 0.1f;
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {
			//negative translation in y-axis
			for (int i = 0; i < 10; i++) {
				cubePositions[i].y -= 0.1f;
			}
		}
		else {
			//decrease rotation rate in y-axis
			ySpeed -= 0.05f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			//increase the scale in z-axis
			zSize += 0.1f;
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {
			//positive translation in z-axis
			for (int i = 0; i < 10; i++) {
				cubePositions[i].z += 0.1f;
			}
		}
		else {
			//increase rotation rate in z-axis
			zSpeed += 0.05f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
			//decrease the scale in z-axis
			zSize -= 0.1f;
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {
			//negative translation in z-axis
			for (int i = 0; i < 10; i++) {
				cubePositions[i].z -= 0.1f;
			}
		}
		else {
			//decrease rotation rate in z-axis
			zSpeed -= 0.05f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		//stop all rotation and reset scale and translation
		xSpeed = 0.0f;
		ySpeed = 0.0f;
		zSpeed = 0.0f;
		xSize = 1.0f;
		ySize = 1.0f;
		zSize = 1.0f;
		xRotation = 0.0f;
		yRotation = 0.0f;
		zRotation = 0.0f;
		for (int i = 0; i < 10; i++) {
			cubePositions[i] = cubeInit[i];
		}
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}



// utility function for loading a 2D texture from file - Note, you might want to create another function for this with GL_CLAMP_TO_EDGE for the texture wrap param
// ---------------------------------------------------
unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}


