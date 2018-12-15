#include "Model.h"

void Model::loadModel(const char *path) {
	FILE *file = fopen(path, "rt");
	char strline[1024];
	char id[128];
	bool hasTexture = false;
	vec3 v, vn;
	vec2 vt;
	vector<vec2> temp_texCoords;
	vector<vec3> temp_normals;
	vec3i t1, t2, t3;

	while (!feof(file)) {
		fscanf(file, "%s", id);
		if (strcmp(id, "v") == 0) {
			//v v.x v.y v.z
			fscanf(file, "%f %f %f\n", &v.x, &v.y, &v.z);
			vertices.push_back(v);
		}
		else if (strcmp(id, "vt") == 0) {
			//vt vt.x vt.y
			hasTexture = true;
			fscanf(file, "%f %f\n", &vt.x, &vt.y);
			temp_texCoords.push_back(vt);
		}
		else if (strcmp(id, "vn") == 0) {
			//vn vn.x vn.y vn.z
			fscanf(file, "%f %f %f\n", &vn.x, &vn.y, &vn.z);
			//temp_normals.push_back(vn);
		}
		else if (strcmp(id, "f") == 0) {
			if (hasTexture) {
				//f 4/1/4 5/2/5 6/3/6
				fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &t1.x, &t1.y, &t1.z, &t2.x, &t2.y, &t2.z, &t3.x, &t3.y, &t3.z);
				//texCoords.push_back(vec2(temp_texCoords[t1.y - 1]));
				//texCoords.push_back(vec2(temp_texCoords[t2.y - 1]));
				//texCoords.push_back(vec2(temp_texCoords[t3.y - 1]));
			}
			else {
				//f 2//1 4//1 1//1
				fscanf(file, "%hu//%hu %hu//%hu %hu//%hu\n", &t1.x, &t1.z, &t2.x, &t2.z, &t3.x, &t3.z);
				t1.y = 0; t2.y = 0; t3.y = 0;
			}
			indices.push_back(vec3u(t1.x - 1, t2.x - 1, t3.x - 1));
			//normals.push_back(temp_normals[t1.z - 1]);
			//normals.push_back(temp_normals[t2.z - 1]);
			//normals.push_back(temp_normals[t3.z - 1]);
		}
		else {
			//info
			fgets(strline, 1024, file);
		}
	}

	/*for (int i = 0; i < vertices.size(); i++) {
		cout << vertices[i].x << " " << vertices[i].y << " " << vertices[i].z << endl;
	}
	cout << endl;
	for (int i = 0; i < indices.size(); i++) {
		cout << indices[i].x << " " << indices[i].y << " " << indices[i].z << endl;
	}
	cout << endl;*/
	fclose(file);
}

void Model::setUpBuffer() {
	ibo = IndexBuffer(&indices[0].x, indices.size() * 3);
	vao.addBuffer(new Buffer(&vertices[0].x, vertices.size() * 3, 3), 0);
	//vao.addBuffer(new Buffer(&texCoords[0].x, texCoords.size() * 3, 2), 1);
}

void Model::Draw() {
	vao.bind();
	ibo.bind();
	
	glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);

	ibo.unbind();
	vao.unbind();
}

