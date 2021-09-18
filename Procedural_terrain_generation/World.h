#pragma once

using namespace std;
#include <iostream>
#include "olcPixelGameEngine.h"
#include <map>
#include "Chunk.h"
//#include "PerlinNoise.hpp"

class World
{
public:
	Chunk::Vec2 CameraPos;

	World();
	~World();

	void Update(float fElapsedTime, Chunk::Vec2 _CameraCoords);
	int GetTile(int x, int y);

	void SetTile(int x, int y);
	void CheckChunks();


private:
	map<Chunk::Vec2, Chunk*> Chunks;
	map<float,int> stringMap;

	int chunksVisibleInViewDst;
	const float MaxViewDst = 20;
	const int chunkSize = 4;
};

