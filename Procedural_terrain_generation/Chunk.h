#pragma once
#include "olcPixelGameEngine.h"
#include "Assets.h"
#include <GenericUsbFnIoctl.h>
#include <stdlib.h>
#include <time.h>


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
		/*Vec2 operator = (const Vec2& c) const
		{
			Vec2 result;
			result.x = c.x;
			result.y = c.y;
			return result;
		}*/
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
		Vec2 operator *= (const Vec2& c) const
		{
			Vec2 result;
			result.x *= c.x;
			result.y *= c.y;
			return result;
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
		Vec2 operator *= (const float& c) const
		{
			Vec2 result;
			result.x *= c;
			result.y *= c;
			return result;
		}
		
	};

	

	int* tiles = nullptr;

	Chunk(Vec2 coord, int _size);
	~Chunk();

	void DrawSelf(olc::PixelGameEngine gfx);
	
	//void PerlinNoise2D(int X1, int Y1, int nWidth, int nHeight, float* fSeed, int nOctaves, float fBias, float* fOutput);

	int GetTile(int x, int y);
	bool SetTile(int x, int y);
	bool SetTile(Vec2 pos);

private:
	Vec2 Pos;
	int size;
	float* seed = nullptr;

};

