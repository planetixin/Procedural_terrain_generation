#include <iostream>
#include "World.h"
#include "Chunk.h"
#include "Assets.h"
#include <stdlib.h>

using namespace std;

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"


class Game: public olc::PixelGameEngine
{
public:
    Game()
    {
        sAppName = "Procedural generation demo";
    }
private:
    Chunk::Vec2 CamPos;
    World world;
    float speed = 8.0f;
    olc::Sprite* tiles;

protected:

    bool OnUserCreate() override
    {
        srand(time(NULL));

        Assets::get().loadSprites();
        tiles = Assets::get().GetSprite("tiles");

        return true;
    }
    bool OnUserUpdate(float fElapsedTime) override
    {
        Clear(olc::BLACK);
        SetPixelMode(olc::Pixel::MASK);
        
        if (IsFocused())
        {
            if (GetKey(olc::W).bHeld)
            {
                CamPos.y += -speed * fElapsedTime;
            }
            if (GetKey(olc::S).bHeld)
            {
                CamPos.y += speed * fElapsedTime;
            }
            if (GetKey(olc::D).bHeld)
            {
                CamPos.x += speed * fElapsedTime;
            }
            if (GetKey(olc::A).bHeld)
            {
                CamPos.x += -speed * fElapsedTime;
            }
            //cout << CamPos.x << " " << CamPos.y << endl;
        }
        
        

        float nTileWidth = 16;
        float nTileHeight = 16;

        Chunk::Vec2 TileCamPos = {(int)CamPos.x, (int)CamPos.y};

        world.Update(fElapsedTime, TileCamPos);

        int nVisibleTilesX = ScreenWidth() / nTileWidth;
        int nVisibleTilesY = ScreenHeight() / nTileHeight;

        float fOffsetX = CamPos.x - (float)nVisibleTilesX/2;
        float fOffsetY = CamPos.y - (float)nVisibleTilesY/2;



        float fTileOffsetX = (fOffsetX - round(fOffsetX)) * nTileWidth;
        float fTileOffsetY = (fOffsetY - round(fOffsetY)) * nTileHeight;

        for (int x = -1; x < nVisibleTilesX+2; x++)
        {
            for (int y = -1; y < nVisibleTilesY+2; y++)
            {
                int idx = world.GetTile(x + round(fOffsetX), y + round(fOffsetY));
                int sx = (idx-1) % 10;
                int sy = (idx-1) / 10;
                if (idx != 0)
                {
                    DrawPartialSprite(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, tiles, sx * nTileWidth, sy * nTileHeight, nTileWidth, nTileHeight);
                }
            }
        }

        return true;
    }
};



int main()
{
    Game demo;
    if (demo.Construct(700, 400, 2, 2, false, false))
        demo.Start();
    return 0;
}