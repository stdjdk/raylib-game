#include "gameobject.h"

//gameobject::gameobject()
//{
//}

gameobject::gameobject(const string& path, const Vector2& pos, const Vector2& dir, int speed)
:m_texture(LoadTexture(path.data()))
,m_position(pos)
,m_direction(dir)
,m_speed(speed)
{
}

gameobject::~gameobject()
{
	UnloadTexture(m_texture);
}

void gameobject::setTexture(const string& path)
{
	m_texture = LoadTexture(path.data());
}

void gameobject::daw(void)
{
	DrawTextureV(m_texture, m_position, WHITE);
}

void gameobject::update(float dt)//dt是一帧的延时值和功能
{
	auto dir = Vector2Normalize(m_direction);

	m_position.x += dir.x * m_speed * dt;
	m_position.y += dir.y * m_speed * dt;
}

void gameobject::event(void)
{
	
}
