#include "Chunk.h"
#include "perlin_noise.h"

Chunk::Chunk(Vec2 coord, int _size)
{
	size = _size;
	Pos.x = coord.x;
	Pos.y = coord.y;

	tiles = new int[size*size];

	//cout << Pos.x << "|" << Pos.y << endl;

	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			Vec2 tilesPos;
			tilesPos.x = (Pos.x*size + x)* 0.15431;
			tilesPos.y = (Pos.y*size + y)* 0.15431;
			int myNoise = (int)(perlin_noise::Perlin2D(tilesPos, 1)) + 1;
			cout << myNoise << " ";

			//int value = siv::PerlinNoise().noise2D(x, y);

			tiles[x + (size*y)] = myNoise;
			
			//cout << Pos.x << "|" << Pos.y << ": " << tiles[x+(y*size)] << endl;
		}
	}

}
Chunk::~Chunk()
{

}

void Chunk::DrawSelf(olc::PixelGameEngine gfx)
{

}


//void Chunk::PerlinNoise2D(int x, int y, float* fSeed, int nOctaves, float fBias, float* fOutput)
//{
//
//		float fNoise = 0.0f;
//		float fScaleAcc = 0.0f;
//		float fScale = 1.0f;
//
//		for (int o = 0; o < nOctaves; o++)
//		{
//			int nPitch = X2 >> o;
//			int nSampleX = (x / nPitch) * nPitch;
//			int nSampleY = (y / nPitch) * nPitch;
//
//			float fBlendX = (float)(x - nSampleX) / (float)nPitch;
//			float fBlendY = (float)(y - nSampleY) / (float)nPitch;
//
//			float fSampleT = (1.0f - fBlendX) * fSeed[nSampleY * Width + nSampleX] + fBlendX * fSeed[nSampleY * Width + nSampleX2];
//			float fSampleB = (1.0f - fBlendX) * fSeed[nSampleY2 * Width + nSampleX] + fBlendX * fSeed[nSampleY2 * Width + nSampleX2];
//
//			fScaleAcc += fScale;
//			fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
//			fScale = fScale / fBias;
//		}
//		
//
//}



int Chunk::GetTile(int x, int y)
{
	if (x > size || y > size || x < 0 || y < 0)
	{
		return 0;
	}
	return (int)tiles[x + (y*size)];
}

bool Chunk::SetTile(int x, int y)
{
	Pos.x = x;
	Pos.y = y;
	return true;
}
bool Chunk::SetTile(Vec2 pos)
{
	Pos.x = pos.x;
	Pos.y = pos.y;
	return true;
}
