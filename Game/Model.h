#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <vector>
#include "shader.h"
#include "buffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"

using namespace std;

class Model {
public:
	Model(const char *path) {
		loadModel(path);
	}
	void setUpBuffer();
	void Draw();

	vector<vec3> vertices;
	vector<vec3> normals;
	vector<vec2> texCoords;
	vector<vec3u> indices;

	VertexArray vao;
	IndexBuffer ibo;

	void loadModel(const char *path);
};