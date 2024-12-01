#include "pch.h"
#include "TilemapActor.h"
#include "Tilemap.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "SceneManager.h"
#include "InputManager.h"


TilemapActor::TilemapActor()
{

}

TilemapActor::~TilemapActor()
{
}

void TilemapActor::BeginPlay()
{
	Super::BeginPlay();
}

void TilemapActor::Tick()
{
	Super::Tick();

	//TickPicking();
}

void TilemapActor::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_tilemap == nullptr || _showDebug == false)
		return;

	const Vec2Int mapSize = _tilemap->GetMapSize();
	const int32 tileSize = _tilemap->GetTileSize();

	vector<vector<Tile>>& tiles = _tilemap->GetTiles();
	vector<Sprite*> sprites;

	for (int i = 0; i <= 9; i++)
	{
		wstring str = L"Tile_" + std::to_wstring(i);
		sprites.push_back(GET_SINGLE(ResourceManager)->GetSprite(str));
	}

	//Vec2Int size = sprite_g->GetSize();
	Vec2Int size = sprites[0]->GetSize();
	Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();

	// 컬링 : 보여야 할 애들만 보여주기
	int32 leftX = ((int32)cameraPos.x - GWinSizeX / 2);
	int32 leftY = ((int32)cameraPos.y - GWinSizeY / 2);
	int32 rightX = ((int32)cameraPos.x + GWinSizeX / 2);
	int32 rightY = ((int32)cameraPos.y + GWinSizeY / 2);

	int32 startX = (leftX - _pos.x) / TILE_SIZEX;
	int32 startY = (leftY - _pos.y) / TILE_SIZEY;
	int32 endX = (rightX - _pos.x) / TILE_SIZEX;
	int32 endY = (rightY - _pos.y) / TILE_SIZEY;


	for (int32 y = startY; y <= endY; y++)
	{
		for (int32 x = startX; x <= endX; x++)
		{
			if (x < 0 || x >= mapSize.x || y < 0 || y >= mapSize.y)
				continue;

			int index = tiles[y][x].value;

			::TransparentBlt(hdc,
				_pos.x + x * TILE_SIZEX - ((int32)cameraPos.x - GWinSizeX / 2),
				_pos.y + y * TILE_SIZEY - ((int32)cameraPos.y - GWinSizeY / 2),
				TILE_SIZEX,
				TILE_SIZEY,
				sprites[index]->GetDC(),
				sprites[index]->GetPos().x,
				sprites[index]->GetPos().y,
				TILE_SIZEX,
				TILE_SIZEY,
				sprites[index]->GetTransparent());
		}
	}
}

void TilemapActor::TickPicking()
{
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
	{
		Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
		int32 screenX = cameraPos.x - GWinSizeX / 2;
		int32 screenY = cameraPos.y - GWinSizeY / 2;

		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		int32 posX = mousePos.x + screenX;
		int32 posY = mousePos.y + screenY;

		int32 x = posX / TILE_SIZEX;
		int32 y = posY / TILE_SIZEY;

		Tile* tile = _tilemap->GetTileAt({ x, y });
		if (tile)
		{
			tile->value = SelectedIndex;
			//if(tile ->value == 2)
			//{
			//}
			//tile->value = 1;
		}


	}

}
