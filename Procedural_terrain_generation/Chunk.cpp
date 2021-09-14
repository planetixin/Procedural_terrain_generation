#include "Chunk.h"



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
			//siv::PerlinNoise::accumulatedOctaveNoise2D_0_1(x, y, 1) ;
			tiles[x + (size*y)] = rand() % 100 + 1;
			
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

void Chunk::PerlindNoise1D(int nCount, float* fSeed, int nOctaves, float *fOutput)
{
	for (int x = 0; x < nCount; x++)
	{
		float fNoise = 0.0f;
		float fScale = 1.0f;
		float fScaleAcc = 0.0f;


		for (int o = 0; o < nOctaves; o++)
		{
			int nPitch = nCount >> o;
			int nSample1 = (x / nPitch) * nPitch;
			int nSample2 = (nSample1 = nPitch) % nCount;

			float fBlend = (float)(x - nSample1)/ (float)nPitch;

			float fSample = (1.0f - fBlend) * fSeed[nSample1] + fBlend * fSeed[nSample2];

			fScaleAcc += fScale;
			fNoise += fSample * fScale;

			fScale = fScale / 2.0f;
		}


		fOutput[x] = fNoise/ fScaleAcc;
	}
}

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
