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
    int putTile = 1;
    olc::Sprite* tiles;

protected:

    bool OnUserCreate() override
    {
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
            if (GetKey(olc::Key::NP_ADD).bPressed)
            {
                putTile += 1;
            }
            if (GetKey(olc::Key::NP_SUB).bPressed)
            {
                putTile -= 1;
            }
            if (GetKey(olc::O).bPressed)
            {
                std::cout << world.CheckSeed() << std::endl;
            }
            //cout << CamPos.x << " " << CamPos.y << endl;
        }
        
        

        float tileSize = 16;

        Chunk::Vec2 TileCamPos = {(int)CamPos.x, (int)CamPos.y};

        world.Update(fElapsedTime, CamPos);
        

        if (GetMouse(0).bPressed)
        {
            int pressedX = round((GetMouseX() - (ScreenWidth() / 2.0f)) / tileSize + CamPos.x);
            int pressedY = round((GetMouseY() - (ScreenHeight() / 2.0f)) / tileSize + CamPos.y);


            world.SetTile(pressedX, pressedY, putTile);

            std::cout <<  pressedX << " " << pressedY << std::endl;
        }
        world.DrawSelf(this, tiles, tileSize);

        

        return true;
    }
};



int main()
{
    srand(time(NULL));
    Game demo;
    if (demo.Construct(400, 300, 3, 3, false, true))
        demo.Start();
    return 0;
}