#include"tilemap.h"
#include<cstdio>
#include<cstring>

// Legend:
// W=1 wall, G=0 grass, V=5 grass variation, D=2 darker grass,
// O=3 stone floor, S=6 sand, B=4 water, T=7 tree, R=8 rock, F=9 flower.
static const char* kMapRows[MAP_ROWS] = {
	"WWWWWWWWWWWWWWWWWWWW",
	"WGSGGGGGDGGGVGGGGGGW",
	"WGSGGTTBBBBDGGRRRGGW",
	"WGSGGTBBBBBDGGRRFGGW",
	"WGSSGGGGGGGGGGGGRGGW",
	"WGGVVGSSSSSSGGGFGGGW",
	"WGGGGGSSSSSSGGGGGGGW",
	"WGGGGGSSSSSSGGVGGGGW",
	"WGGGGSSSOOOSSSGGGGWW",
	"WGGGGSSSOOOSSSGVGGWW",
	"WGGGGSSSSSSSSSGGGGGW",
	"WGGGGGSGGGGGGSGGFGGW",
	"WGDDGGGSGGGGGGSGGGGW",
	"WGGGGGGSGGGGGGGSGGGW",
	"WGGGGGGSGGGGGGGSVGGW",
	"WGTTGGGGGGGGGGGGGRGW",
	"WGGVVGGFGGGGGGGGGRGW",
	"WWWWWWWWWWWWWWWWWWWW"
};

static int CharToTile(char c)
{
	switch (c)
	{
	case 'W': return 1;
	case 'G': return 0;
	case 'V': return 5;
	case 'D': return 2;
	case 'O': return 3;
	case 'S': return 6;
	case 'B': return 4;
	case 'T': return 7;
	case 'R': return 8;
	case 'F': return 9;
	default:  return 0;
	}
}

void TileMap_Init(TileMap* map)
{
	if (!map) return;

	memset(map, 0, sizeof(*map));

	char path[64];
	for (int i = 0; i < 10; i++)
	{
		snprintf(path, sizeof(path), "res/map/%d.png", i);
		map->tiles[i] = LoadTexture(path);
	}

	for (int r = 0; r < MAP_ROWS; r++)
	{
		for (int c = 0; c < MAP_COLS; c++)
		{
			char ch = 0;
			if (c < (int)strlen(kMapRows[r])) ch = kMapRows[r][c];
			map->grid[r][c] = CharToTile(ch);
		}
	}
}

void TileMap_Unload(TileMap* map)
{
	if (!map) return;

	for (int i = 0; i < 10; i++)
	{
		UnloadTexture(map->tiles[i]);
	}
}

void TileMap_Draw(const TileMap* map)
{
	if (!map) return;

	for (int r = 0; r < MAP_ROWS; r++)
	{
		for (int c = 0; c < MAP_COLS; c++)
		{
			int id = map->grid[r][c];
			Rectangle dst = {
				(float)(c * MAP_TILE_SIZE),
				(float)(r * MAP_TILE_SIZE),
				MAP_TILE_SIZE,
				MAP_TILE_SIZE
			};

			if (id < 0 || id >= 10)
			{
				DrawRectangleRec(dst, MAGENTA);
				continue;
			}

			Texture2D t = map->tiles[id];
			if (IsTextureValid(t))
			{
				Rectangle src = { 0, 0, (float)t.width, (float)t.height };
				DrawTexturePro(t, src, dst, { 0, 0 }, 0, WHITE);
			}
			else
			{
				DrawRectangleRec(dst, LIME);
			}
		}
	}
}

int TileMap_IsSolid(const TileMap* map, int row, int col)
{
	if (!map) return 1;
	if (row < 0 || row >= MAP_ROWS || col < 0 || col >= MAP_COLS) return 1;

	int id = map->grid[row][col];
	return id == 1 || id == 4 || id == 7 || id == 8;
}
