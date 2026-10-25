#include "level.h"
#include"player.h"

 level::level()	
 :m_player(make_shared<player>("res/char/0.png"))
{
	TileMap_Init(&m_map);
	m_player->setPosition({ 9 * 64.0f, 8 * 64.0f });

}

level::~level()
{
	TileMap_Unload(&m_map);
}

void level::draw()
{
	ClearBackground(WHITE);
	TileMap_Draw(&m_map);
	m_player->daw();
	DrawFPS(0, 0);
}





void level::update(float dt)
{
	m_player->update(dt);
}



void level::envnt()
{
	m_player->event();

}
