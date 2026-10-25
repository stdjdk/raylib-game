#pragma once
#include"all.h"
class gameobject
{
	public:
//	gameobject();
	gameobject(const string& path, const Vector2& pos = { 0,0 }, const Vector2& dir = { 0,0 }, int speed = 200);
	~gameobject();

	void setTexture(const string& path);
	const Texture& texture()const { return m_texture; }

	void setPosition(const Vector2& pos) { m_position = pos; }
	const Vector2& position()const { return m_position; }
	Vector2& position(){ return m_position; }

	void setDirection(const Vector2& path) { m_direction = path; }
	const Vector2& direction()const { return m_direction; }
	Vector2& direction(){ return m_direction; }

	void setSpeed(int speed) { m_speed = speed; }
	int speed()const { return m_speed; }

public:

	virtual void daw() ;
	virtual void update(float dt);
	virtual void event();

protected:
	Texture2D m_texture;
	Vector2 m_position;
	Vector2 m_direction;
	int m_speed;
};

