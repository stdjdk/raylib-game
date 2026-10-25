#include"all.h"
#include"level.h"
#include<memory>
class game {
public:
     game() {

		InitWindow(64*20,64*18, "ql");
		SetTargetFPS(60);//控制了帧的加载，也同样控制了一秒钟我的整个程序能循环多少次以此可以控制延时加载图片
		m_level.reset(new level);
	}
	~game() {

		CloseWindow();

	}
	int run(void) {
		bool started = false;
		float titleTimer = 0.0f;
		while (!WindowShouldClose())
		{
			float dt = GetFrameTime();
			titleTimer += dt;

			if (!started)
			{
				BeginDrawing();
				m_level->draw();

				int pulse = (int)(55.0f * sinf(titleTimer * 3.0f));
				unsigned char alpha = (unsigned char)(110 + pulse);
				Color fade = { 0, 0, 0, alpha };
				DrawRectangle(0, 0, 64 * 20, 64 * 18, fade);

				int titleY = 180 + (int)(18.0f * sinf(titleTimer * 2.0f));
				DrawText("GRASSLAND RUINS", 160, titleY, 56, GOLD);
				DrawText("Press ENTER or click to start", 400, titleY + 90, 20, WHITE);
				EndDrawing();

				if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					started = true;
				}
				continue;
			}

			BeginDrawing();//绘图
			
			m_level->draw();

			EndDrawing();
			m_level->envnt();
			m_level->update(dt);
		}
		return 0;
	}
private:
	  unique_ptr<level> m_level;

};





int main(void)
{

	game Game;
		return Game.run();
}
