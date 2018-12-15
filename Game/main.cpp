#include "window.h"
#include "Vector.h"
#include "shader.h"
#include "vertexArray.h"
#include "indexBuffer.h"
#include "Model.h"
#include "Camera.h"
#include "World.h"

float WINDOWS_WIDTH = 1280.0f, WINDOWS_HEIGHT = 720.0f;
float deltaTime = 0, lastFrame = 0;
float lastX = WINDOWS_WIDTH / 2.0f, lastY = WINDOWS_HEIGHT / 2.0f;
Camera camera;

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
int main() {

	Window window = Window("Game", WINDOWS_WIDTH, WINDOWS_HEIGHT);

	glfwSetScrollCallback(window.getWindow(), scroll_callback);

	/*Model myModel("source/model/dragon.obj");
	
	VertexArray vao;
	IndexBuffer ibo(&myModel.indices[0].x, myModel.indices.size() * 3);
	vao.addBuffer(new Buffer(&myModel.vertices[0].x, myModel.vertices.size() * 3, 3), 0);

	Shader shader("source/shaders/basic.vert", "source/shaders/basic.frag");
	shader.enable();*/

	World world = World(WorldConfigs());
	Shader shader("terrainVertex.glsl", "terrainFragment.glsl");
	shader.enable();

	glEnable(GL_DEPTH_TEST);
	while (!window.closed()) {
		window.clear();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		//处理鼠标事件
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		double xpos, ypos;

		window.getCursorPosition(xpos, ypos);
		float xoffset = xpos - lastX;
		float yoffset = ypos - lastY;

		lastX = xpos;
		lastY = ypos;

		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE)) {
			camera.ProcessMouseMovement(xoffset, yoffset);
		}
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
			camera.ProcessMouseMovementXY(xoffset, yoffset);
		}

		mat4 projection = mat4::perspective(45.0f, (float)WINDOWS_WIDTH / (float)WINDOWS_HEIGHT, 0.1f, 100.0f);
		mat4 model = mat4::scale(vec3(0.5, 0.5, 0.5));
		mat4 view = camera.getViewMatrix();

		shader.setUniformMat4("projection_matrix", projection);
		shader.setUniformMat4("model_matrix", model);
		shader.setUniformMat4("view_matrix", view);

		for (int z = 0; z < World::CHUNK_COUNT; z++) {
			for (int x = 0; x < World::CHUNK_COUNT; x++) {
				Terrain terrain = world.getTerrain(x, z);
				terrain.bindVAO();
				glDrawElements(GL_TRIANGLES, terrain.getIBO()->getCount(), GL_UNSIGNED_SHORT, 0);
				terrain.unbindVAO();
			}
		}

		/*vao.bind();
		ibo.bind();

		mat4 projection = mat4::perspective(45.0f, (float)WINDOWS_WIDTH / (float)WINDOWS_HEIGHT, 0.1f, 100.0f);
		mat4 model = mat4::scale(vec3(0.08, 0.08, 0.08)) * mat4::translation(vec3(0, -0.5, 0));
		mat4 view = camera.getViewMatrix();

		shader.setUniformMat4("projection_matrix", projection);
		shader.setUniformMat4("model_matrix", model);
		shader.setUniformMat4("view_matrix", view);

		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);

		ibo.unbind();
		vao.unbind();*/

		window.update();
	}
	return 0;
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
	Window *win = (Window *)glfwGetWindowUserPointer(window);
	camera.ProcessMouseScroll(yoffset);
}