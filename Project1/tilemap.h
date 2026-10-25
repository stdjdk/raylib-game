#pragma once
#include"all.h"

#define MAP_ROWS 18
#define MAP_COLS 20
#define MAP_TILE_SIZE 64

typedef struct TileMap
{
	Texture2D tiles[10];
	int grid[MAP_ROWS][MAP_COLS];
} TileMap;

void TileMap_Init(TileMap* map);
void TileMap_Unload(TileMap* map);
void TileMap_Draw(const TileMap* map);
int TileMap_IsSolid(const TileMap* map, int row, int col);
