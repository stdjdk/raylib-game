#pragma once
#include"all.h"
#include"gameobject.h"

class player : public gameobject
{
public:
    using gameobject::gameobject;
    player(const string& path, const Vector2& pos = { 0, 0 }, const Vector2& dir = { 0, 0 }, int speed = 200);

    void event() override;
    void update(float dt);

private:
    unordered_map<string, vector<Texture2D>> m_animationMap;
    int m_frameindex = 0;
    string m_status;
    string m_lastStatus;
    string m_lastFacing = "right";

    float m_frameTimer = 0.0f;
    float m_frameInterval = 0.2f;

    bool m_attacking = false;
    bool m_jumping = false;
    bool m_dashing = false;
    bool m_onGround = true;

    float m_actionTimer = 0.0f;
    float m_dashTimer = 0.0f;
    float m_verticalVelocity = 0.0f;
    float m_groundY = 0.0f;

    Vector2 m_dashDir = { 1, 0 };
};
