#pragma once
#include "Color.h"
#include "WorldConfigs.h"
#include "Terrain.h"
#include "PerlinNoiseGenerator.h"

using namespace std;

class World {
public:
	static const Color BACK_COLOR;           //������ɫ
	static const int CHUNK_COUNT = 5;        //���η�Ϊ5*5��
	static const int SIZE = 100;             //���δ�С
	static const int MAX_ALTITUDE = 8;       //��ߺ���
	static const int DESIRED_VERTEX_COUNT = 138;  //ÿ������138������?

private:
	WorldConfigs configs;
	vector<vector<Terrain>> terrains;

public:
	World(const WorldConfigs &_configs);
	Terrain getTerrain(int gridX, int gridZ);
	vector<vector<Terrain>> getTerrains();
	WorldConfigs getWorldConfigs();
private:
	float generateHeights(vector<vector<float>> &heights, PerlinNoiseGenerator noise);
	void generateTerrains(const vector<vector<float>> &heights, const vector<vector<vec3>> &normals);
	void generateTerrain(int gridX, int gridZ, int chunkLength, const vector<vector<float>> &heights, const vector<vector<vec3>> &normals);
};