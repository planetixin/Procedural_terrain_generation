#include "World.h"


World::World()
{
	chunksVisibleInViewDst = round(MaxViewDst / chunkSize +1)+10;

}

World::~World()
{

}


void World::Update(float fElapsedTime, Chunk::Vec2 _CameraCoords)
{
	
	CameraPos = _CameraCoords;


	int currentChunkCoordX = (CameraPos.x / chunkSize);
	int currentChunkCoordY = (CameraPos.y / chunkSize);


	for (int xOffset = -chunksVisibleInViewDst; xOffset <= chunksVisibleInViewDst; xOffset++)
	{
		for (int yOffset = -chunksVisibleInViewDst; yOffset <= chunksVisibleInViewDst; yOffset++)
		{
			Chunk::Vec2 viewedChunkCoord = { currentChunkCoordX + xOffset, currentChunkCoordY + yOffset };

			float dist = sqrt(pow((CameraPos.x - viewedChunkCoord.x*chunkSize), 2) + pow((CameraPos.y - viewedChunkCoord.y*chunkSize), 2));
			float distx = (CameraPos.x - viewedChunkCoord.x * chunkSize);
			float disty = (CameraPos.x - viewedChunkCoord.x * chunkSize);

			if (Chunks.count(viewedChunkCoord))
			{
				
				if (dist >= MaxViewDst)
				{
					Chunks.erase(viewedChunkCoord);
				}
			}
			else
			{
				if (dist < MaxViewDst)
				{
					Chunks.insert(make_pair(viewedChunkCoord, new Chunk(viewedChunkCoord, chunkSize, noise)));
				}
				
				//cout << xOffset << "|" << yOffset << endl;
			}
		}
	}


}

int World::GetTile(int x, int y)
{
	int ChunkCoordX = floor((float)x / (float)chunkSize);
	int ChunkCoordY = floor((float)y / (float)chunkSize);

	Chunk::Vec2 ChunkCoord{ ChunkCoordX, ChunkCoordY };
	//Chunks[ChunkCoord]->Pos.x == ChunkCoordX && Chunks[ChunkCoord]->Pos.y == ChunkCoordY

	if (Chunks.count(ChunkCoord))
	{
		//GetTile((int)(ChunkCoordX-x), (int)(ChunkCoordY-y))
		Chunk a = *Chunks[ChunkCoord];
		return a.GetTile((int)((x - ChunkCoordX * chunkSize)), (int)(y - (ChunkCoordY * chunkSize)));
	}

	return 0;
}

void World::SetTile(int x, int y, int tile)
{
	int ChunkCoordX = floor((float)x / (float)chunkSize);
	int ChunkCoordY = floor((float)y / (float)chunkSize);

	Chunk::Vec2 ChunkCoord{ ChunkCoordX, ChunkCoordY };

	if (Chunks.count(ChunkCoord))
	{
		//GetTile((int)(ChunkCoordX-x), (int)(ChunkCoordY-y))
		Chunks[ChunkCoord]->SetTile((int)(x - (ChunkCoordX * chunkSize)), (int)(y - (ChunkCoordY * chunkSize)), tile);
		//Chunks[ChunkCoord] = &a;
	}
}

void World::CheckChunks()
{
	for (std::map<Chunk::Vec2, Chunk*>::iterator iter = Chunks.begin(); iter != Chunks.end(); ++iter)
	{
		Chunk::Vec2 k = iter->first;
		cout << k.x << ", " << k.y << endl;
	}
}

void World::DrawSelf(olc::PixelGameEngine* gfx, olc::Sprite *sprite, int tileSize=16)
{
	int nVisibleTilesX = gfx->ScreenWidth() / tileSize;
	int nVisibleTilesY = gfx->ScreenHeight() / tileSize;

	float fOffsetX = CameraPos.x - (float)nVisibleTilesX / 2;
	float fOffsetY = CameraPos.y - (float)nVisibleTilesY / 2;



	float fTileOffsetX = (fOffsetX - round(fOffsetX)) * tileSize;
	float fTileOffsetY = (fOffsetY - round(fOffsetY)) * tileSize;

	for (int x = -1; x < nVisibleTilesX + 2; x++)
	{
		for (int y = -1; y < nVisibleTilesY + 2; y++)
		{
			int idx = GetTile(x + round(fOffsetX), y + round(fOffsetY));
			int sx = (idx - 1) % 10;
			int sy = (idx - 1) / 10;
			if (idx != 0)
			{
				gfx->DrawPartialSprite(x * tileSize - fTileOffsetX, y * tileSize - fTileOffsetY, sprite, sx * tileSize, sy * tileSize, tileSize, tileSize);
			}
		}
	}

}
int World::CheckSeed()
{
	return seed;
}
