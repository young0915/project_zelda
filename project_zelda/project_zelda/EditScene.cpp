#include "pch.h"
#include "EditScene.h"
#include "ResourceManager.h"
#include "SpriteActor.h"
#include "Sprite.h"
#include "Panel.h"
#include "Button.h"
#include "TilemapActor.h"
#include "Tilemap.h"
#include "InputManager.h"

EditScene::EditScene()
{
}

EditScene::~EditScene()
{
}

void EditScene::Init()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"Tile", L"Sprite\\MapTool\\Tile.bmp", RGB(255, 0, 255));

	// TO-DO for 문으로 만들 것.
	GET_SINGLE(ResourceManager)->CreateSprite(L"Tile_0", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 48, 0, 48, 48);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Tile_1", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 0, 0, 48, 48);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Tile_2", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 96, 0, 48, 48);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Tile_3", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 0, 48, 48, 48);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Tile_4", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 48, 48, 48, 48);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Tile_5", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 96, 48, 48, 48);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Tile_6", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 0, 96, 48, 48);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Tile_7", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 48, 96, 48, 48);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Tile_8", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 96, 96, 48, 48);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Tile_9", GET_SINGLE(ResourceManager)->GetTexture(L"Tile"), 0, 144, 48, 48);


	//MapTile
	{
		TilemapActor* actor = new TilemapActor();
		AddActor(actor);

		_tilemapActor = actor;
		{
			auto tm = GET_SINGLE(ResourceManager)->CreateTilemap(L"Tilemap_01");
			tm->SetMapSize({ 20, 20 });
			tm->SetTileSize(48);

			_tilemapActor->SetTilemap(tm);
			_tilemapActor->SetShowMap(true);
		}

		_tilemapActor = actor;
		{
			auto* tm = GET_SINGLE(ResourceManager)->CreateTilemap(L"Tilemap_01");
			tm->SetMapSize({ 20, 20 });
			tm->SetTileSize(48);

			GET_SINGLE(ResourceManager)->LoadTilemap(L"Tilemap_01", L"Tilemap\\Tilemap_01.txt");

			_tilemapActor->SetTilemap(tm);
			_tilemapActor->SetShowMap(true);
		}



		{
			Button* tile1 = new Button();
			tile1->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Tile_1"), BS_Default);
			tile1->SetPos({ 160, 300 });
			tile1->SetSize({ 50	, 50 });
			tile1->AddOnClickDelegate(this, &EditScene::OnClickedTileButton);
			tile1->_selectedIndex = 1;
			_uis.push_back(tile1);

			Button* tile2 = new Button();
			tile2->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Tile_2"), BS_Default);
			tile2->SetPos({ 220, 300 });
			tile2->SetSize({ 50	, 50 });
			tile2->AddOnClickDelegate(this, &EditScene::OnClickedTileButton);
			tile2->_selectedIndex = 2;
			_uis.push_back(tile2);

			Button* tile3 = new Button();
			tile3->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Tile_3"), BS_Default);
			tile3->SetPos({ 280, 300 });
			tile3->SetSize({ 50	, 50 });
			tile3->AddOnClickDelegate(this, &EditScene::OnClickedTileButton);
			tile3->_selectedIndex = 3;
			_uis.push_back(tile3);

			Button* tile4 = new Button();
			tile4->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Tile_4"), BS_Default);
			tile4->SetPos({ 340, 300 });
			tile4->SetSize({ 50	, 50 });
			tile4->AddOnClickDelegate(this, &EditScene::OnClickedTileButton);
			tile4->_selectedIndex = 4;
			_uis.push_back(tile4);

			Button* tile5 = new Button();
			tile5->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Tile_5"), BS_Default);
			tile5->SetPos({ 400, 300 });
			tile5->SetSize({ 50	, 50 });
			tile5->AddOnClickDelegate(this, &EditScene::OnClickedTileButton);
			tile5->_selectedIndex = 5;
			_uis.push_back(tile5);

			Button* tile6 = new Button();
			tile6->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Tile_6"), BS_Default);
			tile6->SetPos({ 460, 300 });
			tile6->SetSize({ 50	, 50 });
			tile6 -> AddOnClickDelegate(this, &EditScene::OnClickedTileButton);
			tile6->_selectedIndex = 6;
			_uis.push_back(tile6);

			Button* tile7 = new Button();
			tile7->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Tile_7"), BS_Default);
			tile7->SetPos({ 520, 300 });
			tile7->SetSize({ 50	, 50 });
			tile7 -> AddOnClickDelegate(this, &EditScene::OnClickedTileButton);
			tile7->_selectedIndex = 7;
			_uis.push_back(tile7);

			Button* tile8 = new Button();
			tile8->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Tile_8"), BS_Default);
			tile8->SetPos({ 580, 300 });
			tile8->SetSize({ 50	, 50 });
			tile8->AddOnClickDelegate(this, &EditScene::OnClickedTileButton);
			tile8->_selectedIndex = 8;
			_uis.push_back(tile8);

			Button* tile9 = new Button();
			tile9->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Tile_9"), BS_Default);
			tile9->SetPos({ 640, 300 });
			tile9->SetSize({ 50	, 50 });
			tile9->AddOnClickDelegate(this, &EditScene::OnClickedTileButton);
			tile9->_selectedIndex = 9;
			_uis.push_back(tile9);
		}


	}


	Super::Init();
}




void EditScene::Update()
{
	Super::Update();


	if (GET_SINGLE(InputManager)->GetButton(KeyType::Q))
	{
		GET_SINGLE(ResourceManager)->SaveTilemap(L"Tilemap_01", L"Tilemap\\Tilemap_01.txt");
	}
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::E))
	{
		GET_SINGLE(ResourceManager)->LoadTilemap(L"Tilemap_01", L"Tilemap\\Tilemap_01.txt");
	}

}

void EditScene::Render(HDC hdc)
{
	Super::Render(hdc);
}


void EditScene::OnClickedTileButton(int index)
{
	_tilemapActor->SelectedIndex = index;
}
