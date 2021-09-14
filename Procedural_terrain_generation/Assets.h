#pragma once

using namespace std;
#include "olcPixelGameEngine.h"

#include <map>

class Assets
{
public:
	static Assets& get()
	{

		static Assets me;
		return me;
	}

	Assets(Assets const&) = delete;
	void operator=(Assets const&) = delete;

	olc::Sprite* GetSprite(string name)
	{
		return m_mapSprites[name];
	}

	void loadSprites();
	

private:
	Assets();
	~Assets();

	map<string, olc::Sprite*> m_mapSprites;
};

