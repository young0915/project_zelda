#include "pch.h"
#include "BattleScene.h"
#include "TilemapActor.h"
#include "Tilemap.h"
#include "ResourceManager.h"
#include "AI.h"
#include "Flipbook.h"
#include "SpriteActor.h"
#include "Sprite.h"
BattleScene::BattleScene()
{
}

BattleScene::~BattleScene()
{
}

void BattleScene::Init()
{
	// Load Resource
	GET_SINGLE(ResourceManager)->LoadTexture(L"Tile", L"Sprite\\MapTool\\Tile.bmp", RGB(255, 0, 255));
	
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerDown", L"Sprite\\Player\\PlayerDown.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerUp", L"Sprite\\Player\\PlayerUp.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerLeft", L"Sprite\\Player\\PlayerLeft.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerRight", L"Sprite\\Player\\PlayerRight.bmp", RGB(128, 128, 128));
	
	GET_SINGLE(ResourceManager)->LoadTexture(L"Moblin_S", L"Sprite\\Monster\\Moblin_S.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Moblin_A", L"Sprite\\Monster\\Moblin_A.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Octoroc", L"Sprite\\Monster\\Octoroc.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Zol", L"Sprite\\Monster\\Zol.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Darknut", L"Sprite\\Monster\\Darknut.bmp", RGB(128, 128, 128));
	GET_SINGLE(ResourceManager)->LoadTexture(L"Bat", L"Sprite\\Monster\\Bat.bmp", RGB(128, 128, 128));

	
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



	 // Tile Load
	{
		TilemapActor* actor = new TilemapActor();
		AddActor(actor);

		_tilemapActor = actor;
		{
			auto* tm = GET_SINGLE(ResourceManager)->CreateTilemap(L"Tilemap_01");
			tm->SetMapSize({ 20, 20 });
			tm->SetTileSize(48);

			GET_SINGLE(ResourceManager)->LoadTilemap(L"Tilemap_01", L"Tilemap\\Tilemap_01.txt");

			_tilemapActor->SetTilemap(tm);
			_tilemapActor->SetShowMap(true);
		}
	}
	
#pragma region Octoroc Ani
	// Move
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Octoroc");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveDown_Octoroc");
		fb->SetInfo({ texture, L"FB_MoveDown_Octoroc", {100, 100}, 0, 1, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Octoroc");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveLeft_Octoroc");
		fb->SetInfo({ texture, L"FB_MoveLeft_Octoroc", {100, 100}, 0, 1, 2, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Octoroc");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveRight_Octoroc");
		fb->SetInfo({ texture, L"FB_MoveRight_Octoroc", {100, 100}, 0, 1, 4, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Octoroc");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveUp_Octoroc");
		fb->SetInfo({ texture, L"FB_MoveUp_Octoroc", {100, 100}, 0, 1, 6, 0.5f });
	}
	// Attack
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Octoroc");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackDown_Octoroc");
		fb->SetInfo({ texture, L"FB_MoveDown_Octoroc", {100, 100}, 0, 1, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Octoroc");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackLeft_Octoroc");
		fb->SetInfo({ texture, L"FB_MoveLeft_Octoroc", {100, 100}, 0, 1, 3, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Octoroc");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackRight_Octoroc");
		fb->SetInfo({ texture, L"FB_MoveRight_Octoroc", {100, 100}, 0, 1, 5, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Octoroc");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackUp_Octoroc");
		fb->SetInfo({ texture, L"FB_MoveUp_Octoroc", {100, 100}, 0, 1, 7, 0.5f });
	}
#pragma endregion

#pragma region Darknut Ani
	// 
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Darknut");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveDown_Darknut");
		fb->SetInfo({ texture, L"FB_MoveDown_Darknut", {300, 300}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Darknut");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveLeft_Darknut");
		fb->SetInfo({ texture, L"FB_MoveLeft_Darknut", {300, 300}, 0, 3, 2, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Darknut");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveRight_Darknut");
		fb->SetInfo({ texture, L"FB_MoveRight_Darknut", {300, 300}, 0, 3, 4, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Darknut");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveUp_Darknut");
		fb->SetInfo({ texture, L"FB_MoveUp_Darknut",{300, 300}, 0, 3, 6, 0.5f });
	}

	//Attack
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Darknut");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackDown_Darknut");
		fb->SetInfo({ texture, L"FB_MoveDown_Darknut", {300, 300}, 0, 5, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Darknut");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackLeft_Darknut");
		fb->SetInfo({ texture, L"FB_MoveLeft_Darknut", {300, 300}, 0, 5, 3, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Darknut");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackRight_Darknut");
		fb->SetInfo({ texture, L"FB_MoveRight_Darknut", {300, 300}, 0, 5, 5, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Darknut");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackUp_Darknut");
		fb->SetInfo({ texture, L"FB_MoveUp_Darknut",{300, 300}, 0,5, 7, 0.5f });
	}
#pragma endregion

#pragma region Moblin_A Ani
	// 
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Moblin_S");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveDown_Moblin_S");
		fb->SetInfo({ texture, L"FB_MoveDown_Moblin_S", {300, 300}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Moblin_S");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveLeft_Moblin_S");
		fb->SetInfo({ texture, L"FB_MoveLeft_Moblin_S", {300, 300},  0, 3, 2, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Moblin_S");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveRight_Moblin_S");
		fb->SetInfo({ texture, L"FB_MoveRight_Moblin_S", {300, 300}, 0, 3, 4, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Moblin_S");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveUp_Moblin_S");
		fb->SetInfo({ texture, L"FB_MoveUp_Moblin_S",{300, 300},  0,3, 6, 0.5f });
	}

	//Attack
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Moblin_S");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackDown_Moblin_S");
		fb->SetInfo({ texture, L"FB_MoveDown_Moblin_S", {300, 300}, 0, 3, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Moblin_S");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackLeft_Moblin_S");
		fb->SetInfo({ texture, L"FB_MoveLeft_Moblin_S", {300, 300},  0, 3, 3, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Moblin_S");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackRight_Moblin_S");
		fb->SetInfo({ texture, L"FB_MoveRight_Moblin_S", {300, 300}, 0, 3, 5, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Moblin_S");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackUp_Moblin_S");
		fb->SetInfo({ texture, L"FB_MoveUp_Moblin_S",{300, 300},  0,3, 7, 0.5f });
	}
#pragma endregion

#pragma region Moblin_S Ani
	// 
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Moblin_A");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveDown_Moblin_A");
		fb->SetInfo({ texture, L"FB_MoveDown_Moblin_A", {300, 300}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Moblin_A");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveLeft_Moblin_A");
		fb->SetInfo({ texture, L"FB_MoveLeft_Moblin_A", {300, 300},  0, 3, 2, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Moblin_A");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveRight_Moblin_A");
		fb->SetInfo({ texture, L"FB_MoveRight_Moblin_A", {300, 300}, 0, 3, 4, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Moblin_A");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveUp_Moblin_A");
		fb->SetInfo({ texture, L"FB_MoveUp_Moblin_A",{300, 300},  0,3, 6, 0.5f });
	}

	//Attack
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Moblin_A");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackDown_Moblin_A");
		fb->SetInfo({ texture, L"FB_MoveDown_Moblin_A", {300, 300}, 0, 3, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Moblin_A");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackLeft_Moblin_A");
		fb->SetInfo({ texture, L"FB_MoveLeft_Moblin_A", {300, 300},  0, 3, 3, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Moblin_A");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackRight_Moblin_A");
		fb->SetInfo({ texture, L"FB_MoveRight_Darknut", {300, 300}, 0, 3, 5, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Moblin_A");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackUp_Moblin_A");
		fb->SetInfo({ texture, L"FB_MoveUp_Moblin_A",{300, 300},  0,3, 7, 0.5f });
	}
#pragma endregion

#pragma region Bat ani
	// 
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Bat");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveDown_Bat");
		fb->SetInfo({ texture, L"FB_MoveDown_Bat", {50, 50}, 0, 3, 0, 0.5f });
	}
	
#pragma endregion

#pragma region Zol ani
	// Move
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Zol");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveDown_Zol");
		fb->SetInfo({ texture, L"FB_MoveDown_Zol", {50, 50}, 0, 2, 0, 0.5f });
	}

	// Move
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Zol");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackDown_Zol");
		fb->SetInfo({ texture, L"FB_MoveDown_Zol", {50, 50}, 0, 3, 0, 0.5f });
	}
#pragma endregion

	

	// AI Load
	{
		/*
		AIInfo playerInfo;
		playerInfo.maxHp = 10;
		playerInfo.dmg = 5;
		playerInfo.speed = 10.0f;
		AI* player = new AI(L"Link", playerInfo, AITYPE::HERO, AttackType::MELEE_ATTACK, { 0,0 });
		AddActor(player);
		*/

		//// darknut
		AIInfo darknutInfo;
		darknutInfo.maxHp = 10;
		darknutInfo.dmg = 5;
		darknutInfo.speed = 10.0f;
		AI* darknut = new AI(L"Darknut", darknutInfo, AITYPE::MONSTER, AttackType::MELEE_ATTACK, { 0,0 });
		AddActor(darknut);


		//// Bow Moblin
		AIInfo bow_moblinInfo;
		bow_moblinInfo.maxHp = 10;
		bow_moblinInfo.dmg = 5;
		bow_moblinInfo.speed = 10.0f;
		AI* bow_moblin = new AI(L"Moblin_A", bow_moblinInfo, AITYPE::MONSTER, AttackType::MELEE_ATTACK, { 0,0 });
		AddActor(bow_moblin);

		////Spear Moblin
		AIInfo spear_moblinInfo;
		spear_moblinInfo.maxHp = 10;
		spear_moblinInfo.dmg = 5;
		spear_moblinInfo.speed = 10.0f;
		AI* spear_moblin = new AI(L"Moblin_S", spear_moblinInfo, AITYPE::MONSTER, AttackType::MELEE_ATTACK, { 0,0 });
		AddActor(spear_moblin);

		// Octorok
		AIInfo octorokInfo;
		octorokInfo.maxHp = 10;
		octorokInfo.dmg = 5;
		octorokInfo.speed = 10.0f;
		AI* octorok = new AI(L"Octoroc", octorokInfo, AITYPE::MONSTER, AttackType::MELEE_ATTACK, { 0,0 });
		octorok->SetPos({ 100, 100 });
		AddActor(octorok);

		AIInfo zolInfo;
		zolInfo.maxHp = 10;
		zolInfo.dmg = 5;
		zolInfo.speed = 10.0f;
		AI* zol = new AI(L"Zol", zolInfo, AITYPE::MONSTER, AttackType::MELEE_ATTACK, { 0,0 });
		AddActor(zol);

		AIInfo KeeseInfo;
		KeeseInfo.maxHp = 10;
		KeeseInfo.dmg = 5;
		KeeseInfo.speed = 10.0f;
		AI* Keese = new AI(L"Bat", zolInfo, AITYPE::MONSTER, AttackType::MELEE_ATTACK, { 0,0 });
		AddActor(Keese);
	}




	Super::Init();
}

void BattleScene::Update()
{
	Super::Update();


	// Data 불러오기
	// 

}

void BattleScene::Render(HDC hdc)
{
	Super::Render(hdc);

}

bool BattleScene::CanGo(Vec2Int cellPos)
{
	return false;
}

Vec2 BattleScene::ConvertPos(Vec2Int cellPos)
{
	Vec2 ret = {};

	if (_tilemapActor == nullptr)
		return ret;

	Tilemap* tm = _tilemapActor->GetTilemap();
	if (tm == nullptr)
		return ret;

	int32 size = tm->GetTileSize();
	Vec2 pos = _tilemapActor->GetPos();

	ret.x = pos.x + cellPos.x * size + (size / 2);
	ret.y = pos.y + cellPos.y * size + (size / 2);

	return ret;
}
