#include "Assets.h"


Assets::Assets()
{

}
Assets::~Assets()
{

}

void Assets::loadSprites()
{
	auto load = [&](string sName, string sFileName)
	{
		olc::Sprite* s = new olc::Sprite(sFileName);
		m_mapSprites[sName] = s;
	};
	
	load("tiles", "data/gfx/tiles.png");
	load("player", "data/gfx/player.png");
}