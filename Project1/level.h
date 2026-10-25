#pragma once
#include"all.h"
#include"gameobject.h"
#include"tilemap.h"
#include<memory>
class level
{
public:
	 level();
	 ~level();

	void draw();
	void update(float dt);
	void envnt();
private:

	TileMap m_map;
	shared_ptr<gameobject> m_player;
};

