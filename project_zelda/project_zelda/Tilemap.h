#pragma once
#include "ResourceBase.h"

struct Tile
{
	// TODO
	// 0 -> ¹ÙÅÁÈ­¸é
 	// 1 -> ¹Ù´Ú
	// 2 -> Tile_wall_T_R
	// 3 -> Tile_wall_T_L
	// 4 -> Tile_wall_B_L
	// 5 -> Tile_wall_B_R
	// 6 -> Tile_wall_R
	// 7 -> Tile_wall_L
	// 8 -> Tile_wall_T
	// 9 -> Tile_wall_B
	int32 value = 0;
};

class Tilemap : public ResourceBase
{
public:
	Tilemap();
	virtual ~Tilemap() override;

	virtual void LoadFile(const wstring& path) override;
	virtual void SaveFile(const wstring& path) override;

	Vec2Int GetMapSize() { return _mapSize; }
	int32 GetTileSize() { return _tileSize; }
	Tile* GetTileAt(Vec2Int pos);
	vector<vector<Tile>>& GetTiles() { return _tiles; };

	void SetMapSize(Vec2Int size);
	void SetTileSize(int32 size);

private:
	Vec2Int _mapSize = {};
	int32 _tileSize = {};
	vector<vector<Tile>> _tiles;
};

