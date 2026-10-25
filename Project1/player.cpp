#include "player.h"
#include "texturemanger.h"

player::player(const string& path, const Vector2& pos, const Vector2& dir, int speed)
    : gameobject(path, pos, dir, speed)
{
    m_animationMap["char"]      = texturemanger::importFolder("res/char", "png");
    m_animationMap["charright"] = texturemanger::importFolder("res/charright", "png");
    m_animationMap["charleft"]  = texturemanger::importFolder("res/charleft", "png");
    m_animationMap["charup"]    = texturemanger::importFolder("res/charup", "png");
    m_animationMap["chardown"]  = texturemanger::importFolder("res/chardown", "png");
    m_animationMap["charjump"]  = texturemanger::importFolder("res/charjump", "png");
    m_animationMap["charattack"]= texturemanger::importFolder("res/charattack", "png");
    m_animationMap["chardash"]  = texturemanger::importFolder("res/chardash", "png");
    m_animationMap["charidleleft"]  = texturemanger::importFolder("res/charidleleft", "png");
    m_animationMap["charidleup"]    = texturemanger::importFolder("res/charidleup", "png");
    m_animationMap["charidledown"]  = texturemanger::importFolder("res/charidledown", "png");
    m_animationMap["charidleright"] = texturemanger::importFolder("res/charidleright", "png");
    m_animationMap["charattackleft"]= texturemanger::importFolder("res/charattackleft", "png");
    m_animationMap["charattackup"]  = texturemanger::importFolder("res/charattackup", "png");
    m_animationMap["charattackdown"]= texturemanger::importFolder("res/charattackdown", "png");

    m_groundY = 8 * 64.0f;
}

void player::event()
{
    bool left  = IsKeyDown(KEY_LEFT);
    bool right = IsKeyDown(KEY_RIGHT);
    bool up    = IsKeyDown(KEY_UP);
    bool down  = IsKeyDown(KEY_DOWN);

    if (!m_dashing && !m_attacking)
    {
        direction().x = 0.0f;
        direction().y = 0.0f;
        if (right) direction().x += 1.0f;
        if (left)  direction().x -= 1.0f;
        if (down)  direction().y += 1.0f;
        if (up)    direction().y -= 1.0f;
    }

    if (IsKeyPressed(KEY_SPACE) && m_onGround)
    {
        m_jumping         = true;
        m_onGround        = false;
        m_verticalVelocity = -620.0f;
    }

    if (IsKeyPressed(KEY_J) && !m_attacking && !m_dashing)
    {
        m_attacking = true;
        m_actionTimer = 0.35f;
    }

    if ((IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_RIGHT_SHIFT)) && !m_dashing)
    {
        m_dashing  = true;
        m_dashTimer = 0.25f;

        Vector2 facing = { direction().x, direction().y };
        if (facing.x == 0.0f && facing.y == 0.0f)
            facing = { 1.0f, 0.0f };

        m_dashDir = Vector2Normalize(facing);
    }
}

void player::update(float dt)
{
    if (m_attacking)
    {
        m_actionTimer -= dt;
        if (m_actionTimer <= 0.0f)
            m_attacking = false;

        if (m_lastFacing == "left")
            m_status = "charattackleft";
        else if (m_lastFacing == "up")
            m_status = "charattackup";
        else if (m_lastFacing == "down")
            m_status = "charattackdown";
        else
            m_status = "charattack";
    }
    else if (m_dashing)
    {
        m_dashTimer -= dt;
        if (m_dashTimer <= 0.0f)
            m_dashing = false;

        m_status = "chardash";
        direction() = m_dashDir;
        m_speed = 650;
        gameobject::update(dt);
    }
    else if (m_jumping)
    {
        m_verticalVelocity += 1400.0f * dt;
        position().y += m_verticalVelocity * dt;

        if (position().y >= m_groundY)
        {
            position().y = m_groundY;
            m_verticalVelocity = 0.0f;
            m_onGround = true;
            m_jumping = false;
        }

        m_status = "charjump";
        m_speed = 200;
        if (Vector2Length(direction()) > 0.001f)
            gameobject::update(dt);
    }
    else
    {
        if (direction().x > 0.1f)
        {
            m_status = "charright";
            m_lastFacing = "right";
        }
        else if (direction().x < -0.1f)
        {
            m_status = "charleft";
            m_lastFacing = "left";
        }
        else if (direction().y < -0.1f)
        {
            m_status = "charup";
            m_lastFacing = "up";
        }
        else if (direction().y > 0.1f)
        {
            m_status = "chardown";
            m_lastFacing = "down";
        }
        else
        {
            if (m_lastFacing == "left")
                m_status = "charidleleft";
            else if (m_lastFacing == "up")
                m_status = "charidleup";
            else if (m_lastFacing == "down")
                m_status = "charidledown";
            else
                m_status = "charidleright";
        }

        m_speed = 200;
        if (Vector2Length(direction()) > 0.001f)
            gameobject::update(dt);
    }

    float interval = 0.10f;
    if (m_status == "charattack" || m_status == "charattackleft" || m_status == "charattackup" || m_status == "charattackdown" || m_status == "chardash" || m_status == "charjump")
        interval = 0.06f;

    auto it = m_animationMap.find(m_status);
    if (it == m_animationMap.end())
        return;

    auto& frames = it->second;
    if (frames.empty())
        return;

    if (m_status != m_lastStatus)
    {
        m_lastStatus = m_status;
        m_frameindex = 0;
        m_frameTimer = 0.0f;
    }

    m_frameTimer += dt;
    if (m_frameTimer >= interval)
    {
        m_frameTimer = 0.0f;
        m_frameindex++;
        if (m_frameindex >= (int)frames.size())
            m_frameindex = 0;
    }

    m_texture = frames[m_frameindex];
}
