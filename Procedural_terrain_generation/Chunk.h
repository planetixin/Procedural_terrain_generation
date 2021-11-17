#pragma once
#include "olcPixelGameEngine.h"
#include "Assets.h"
#include <GenericUsbFnIoctl.h>
#include <stdlib.h>
#include <time.h>
#include "OpenSimplexNoise.h"

class Chunk
{	
public:
	struct Vec2
	{
		float x = 0;
		float y = 0;
		bool operator < (const Vec2& c) const
		{
			return std::tie(x, y) < std::tie(c.x, c.y);
		}
		bool operator > (const Vec2& c) const
		{
			return std::tie(x, y) > std::tie(c.x, c.y);
		}
		bool operator == (const Vec2& c) const
		{
			return (this->x == c.x && this->y == c.y);
		}
		void operator = (const Vec2& c)
		{
			x = c.x;
			y = c.y;
		}
		Vec2 operator * (const Vec2& c) const
		{
			Vec2 result;
			result.x = result.x * c.x;
			result.y = result.y * c.y;
			return result;
		}
		Vec2 operator / (const Vec2& c) const
		{
			Vec2 result;
			result.x = result.x / c.x;
			result.y = result.y / c.y;
			return result;
		}
		void operator *= (const Vec2& c)
		{
			x *= c.x;
			y *= c.y;
		}
		Vec2 operator * (const float& c) const
		{
			Vec2 result;
			result.x = result.x * c;
			result.y = result.y * c;
			return result;
		}
		Vec2 operator / (const float& c) const
		{
			Vec2 result;
			result.x = result.x / c;
			result.y = result.y / c;
			return result;
		}
		void operator *= (const float& c)
		{
			x *= c;
			y *= c;
		}
		
	};

	int* tiles = nullptr;

	Chunk(Vec2 coord, int _size, OpenSimplexNoise::Noise noise);
	~Chunk();

	void DrawSelf(olc::PixelGameEngine gfx);
	
	//void PerlinNoise2D(int X1, int Y1, int nWidth, int nHeight, float* fSeed, int nOctaves, float fBias, float* fOutput);

	int GetTile(int x, int y);
	bool SetTile(int x, int y, int tile);
	bool SetTile(Vec2 pos, int tile);

private:
	Vec2 Pos;
	int size;
	float* seed = nullptr;

};

