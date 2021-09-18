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
					Chunks.insert(make_pair(viewedChunkCoord, new Chunk(viewedChunkCoord, chunkSize)));
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

void World::SetTile(int x, int y)
{
	int ChunkCoordX = round((float)x / (float)chunkSize);
	int ChunkCoordY = round((float)y / (float)chunkSize);

	Chunk::Vec2 ChunkCoord{ (float)ChunkCoordX, (float)ChunkCoordY };

	if (Chunks.count(ChunkCoord))
	{
		//GetTile((int)(ChunkCoordX-x), (int)(ChunkCoordY-y))
		Chunk a = *Chunks[ChunkCoord];
		a.SetTile((int)((ChunkCoordX * chunkSize) - x), (int)((ChunkCoordY * chunkSize) - y));
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