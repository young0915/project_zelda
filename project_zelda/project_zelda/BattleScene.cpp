#include "pch.h"
#include "BattleScene.h"
#include "TilemapActor.h"
#include "Tilemap.h"
#include "ResourceManager.h"
#include "Flipbook.h"
#include "SpriteActor.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Enemy.h"
#include "Hero.h"
#include	"Projectile.h"

BattleScene::BattleScene()
{
}

BattleScene::~BattleScene()
{
}

void BattleScene::Init()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"Tile", L"Sprite\\MapTool\\Tile.bmp", RGB(255, 0, 255));

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
	
	GET_SINGLE(ResourceManager)->LoadTexture(L"Arrow", L"Sprite\\Item\\ArrowBullet.bmp", RGB(128, 128, 128));

	LoadResource(_stageIndex);
	// Tile Load
	SetStage(_stageIndex);
	// stage 
	SpawnEnemy(_stageIndex);

	if (!_heroDataLoad)
	{
		// Player
		{
			AIStatus playerStatus;
			playerStatus.maxHp = 100000000;
			playerStatus.dmg = 5;
			playerStatus.speed = 200.0f;
			playerStatus.attackDistance = 1;
			Hero* player = new Hero(L"Link", playerStatus, AITYPE::HERO, AttackType::MELEE_ATTACK, { 8,9 }, 0.5f);
			AddActor(player);
		}

		_heroDataLoad = true;
	}



	Super::Init();
}

void BattleScene::Update()
{
	Super::Update();

	if (_actors[LAYER_MONSTER].size() <= 0)
	{
		if (_stageIndex < 6)
		{
			_stageIndex++;
			Init();
		}
	}

	// cheat
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		AIClear();
		if (_stageIndex < 6)
		{
			_stageIndex++;
			Init();
		}
	}
	// Data 불러오기
	// 

}

void BattleScene::Render(HDC hdc)
{
	Super::Render(hdc);

}

void BattleScene::LoadResource(int stage)
{
	switch (stage)
	{
	case 1:
#pragma region Bat ani
		// 
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Bat");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveDown_Bat");
		fb->SetInfo({ texture, L"FB_MoveDown_Bat", {50, 50}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Bat");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveLeft_Bat");
		fb->SetInfo({ texture, L"FB_MoveLeft_Bat", {50, 50}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Bat");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveRight_Bat");
		fb->SetInfo({ texture, L"FB_MoveRight_Bat", {50, 50}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Bat");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveUp_Bat");
		fb->SetInfo({ texture, L"FB_MoveUp_Bat", {50, 50}, 0, 3, 0, 0.5f });
	}

	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Bat");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackDown_Bat");
		fb->SetInfo({ texture, L"FB_MoveDown_Bat", {50, 50}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Bat");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackLeft_Bat");
		fb->SetInfo({ texture, L"FB_MoveLeft_Bat", {50, 50}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Bat");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackRight_Bat");
		fb->SetInfo({ texture, L"FB_MoveRight_Bat", {50, 50}, 0, 3, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Bat");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackUp_Bat");
		fb->SetInfo({ texture, L"FB_MoveUp_Bat", {50, 50}, 0, 3, 0, 0.5f });
	}

#pragma endregion

#pragma region Zol ani
	// Move
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Zol");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveDown_Zol");
		fb->SetInfo({ texture, L"FB_MoveDown_Zol", {50, 50}, 0, 2, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Zol");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveLeft_Zol");
		fb->SetInfo({ texture, L"FB_MoveLeft_Zol", {50, 50}, 0, 2, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Zol");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveRight_Zol");
		fb->SetInfo({ texture, L"FB_MoveRight_Zol", {50, 50}, 0, 2, 0, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Zol");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveUp_Zol");
		fb->SetInfo({ texture, L"FB_MoveUp_Zol", {50, 50}, 0, 2, 0, 0.5f });
	}

	// Attack
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Zol");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackDown_Zol");
		fb->SetInfo({ texture, L"FB_MoveDown_Zol", {50, 50}, 0, 3, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Zol");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackLeft_Zol");
		fb->SetInfo({ texture, L"FB_MoveLeft_Zol", {50, 50}, 0, 3, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Zol");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackRight_Zol");
		fb->SetInfo({ texture, L"FB_MoveRight_Zol", {50, 50}, 0, 3, 1, 0.5f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Zol");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackUp_Zol");
		fb->SetInfo({ texture, L"FB_MoveUp_Zol", {50, 50}, 0, 3, 1, 0.5f });
	}
#pragma endregion
	break;

	case 2:
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
	// Item
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Octoroc");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_Octoroc_Item");
		fb->SetInfo({ texture, L"FB_Octoroc_Item", {100, 100}, 0, 2, 9, 0.5f });
	}

#pragma endregion
	break;

	case 3:
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
	break;

	case 4:
#pragma region Darknut Ani
		// 
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Darknut");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveDown_Darknut");
		fb->SetInfo({ texture, L"FB_MoveDown_Darknut", {300, 300}, 0, 3, 6, 0.5f });
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
		fb->SetInfo({ texture, L"FB_MoveUp_Darknut",{300, 300}, 0, 3, 0, 0.5f });
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

	break;
	case 5:
		break;
	}
#pragma region  Hero
	{
		// IDLE
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerUp");
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_IdleUp_Link");
			fb->SetInfo({ texture, L"FB_MoveUp_Link", {200, 200}, 0, 9, 0, 0.5f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerDown");
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_IdleDown_Link");
			fb->SetInfo({ texture, L"FB_MoveDown_Link", {200, 200}, 0, 9, 0, 0.5f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerLeft");
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_IdleLeft_Link");
			fb->SetInfo({ texture, L"FB_MoveLeft_Link", {200, 200}, 0, 9, 0, 0.5f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerRight");
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_IdleRight_Link");
			fb->SetInfo({ texture, L"FB_MoveRight_Link", {200, 200}, 0, 9, 0, 0.5f });
		}
		// MOVE
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerUp");
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveUp_Link");
			fb->SetInfo({ texture, L"FB_MoveUp_Link", {200, 200}, 0, 9, 1, 0.5f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerDown");
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveDown_Link");
			fb->SetInfo({ texture, L"FB_MoveDown_Link", {200, 200}, 0, 9, 1, 0.5f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerLeft");
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveLeft_Link");
			fb->SetInfo({ texture, L"FB_MoveLeft_Link", {200, 200}, 0, 9, 1, 0.5f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerRight");
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveRight_Link");
			fb->SetInfo({ texture, L"FB_MoveRight_Link", {200, 200}, 0, 9, 1, 0.5f });
		}
		// Attack 1
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerUp");
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackUp_Link");
			fb->SetInfo({ texture, L"FB_MoveUp_Link", {200, 200}, 0, 7, 3, 0.5f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerDown");
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackDown_Link");
			fb->SetInfo({ texture, L"FB_MoveDown_Link", {200, 200}, 0, 7, 3, 0.5f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerLeft");
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackLeft_Link");
			fb->SetInfo({ texture, L"FB_MoveLeft_Link", {200, 200}, 0, 7, 3, 0.5f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerRight");
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackRight_Link");
			fb->SetInfo({ texture, L"FB_MoveRight_Link", {200, 200}, 0, 7, 3, 0.5f });
		}
		// Attack 2
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerUp");
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackBowUp_Link");
			fb->SetInfo({ texture, L"FB_MoveUp_Link", {200, 200}, 0, 9, 5, 0.5f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerDown");
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackBowDown_Link");
			fb->SetInfo({ texture, L"FB_MoveDown_Link", {200, 200}, 0, 9, 5, 0.5f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerLeft");
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackBowLeft_Link");
			fb->SetInfo({ texture, L"FB_MoveLeft_Link", {200, 200}, 0, 9, 5, 0.5f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerRight");
			Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_AttackBowRight_Link");
			fb->SetInfo({ texture, L"FB_MoveRight_Link", {200, 200}, 0, 9,5, 0.5f });
		}
	}
#pragma endregion

	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Arrow");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ArrowDown_Item");
		fb->SetInfo({ texture, L"FB_ArrowDown_Item", {100, 100}, 0, 0, 0, 0.1f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Arrow");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ArrowLeft_Item");
		fb->SetInfo({ texture, L"FB_ArrowLeft_Item", {100, 100}, 0, 0, 1, 0.1f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Arrow");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ArrowRight_Item");
		fb->SetInfo({ texture, L"FB_ArrowRight_Item", {100, 100}, 0, 0, 2, 0.1f });
	}
	{
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Arrow");
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_ArrowUp_Item");
		fb->SetInfo({ texture, L"FB_ArrowUp_Item", {100, 100}, 0, 0, 3, 0.1f });
	}
}

void BattleScene::SetStage(int stage)
{
	// TO-DO 바이너리 파일로 바꿔놓을 것
	wstring stageName;

	switch (stage)
	{
	case 1:
	case 2:
	case 3:
	case 4:
		stageName = L"Tilemap_01";
		break;
	case 5:
		stageName = L"Tilemap_Boss";
		break;
	}

	TilemapActor* actor = new TilemapActor();
	AddActor(actor);
	_tilemapActor = actor;
	{
		auto* tm = GET_SINGLE(ResourceManager)->CreateTilemap(stageName);
		tm->SetMapSize({ 20, 20 });
		tm->SetTileSize(48);

		GET_SINGLE(ResourceManager)->LoadTilemap(stageName, L"Tilemap\\" + stageName + L".txt");

		_tilemapActor->SetTilemap(tm);
		_tilemapActor->SetShowMap(true);
	}
}

void BattleScene::SpawnEnemy(int stage)
{
	switch (stage)
	{
	case 1:
		// zol 4, bat 2 
		for (int i = 0; i < 4; i++)
		{
			Vec2Int pos = { 3 + (i % 2) * 10, 3 + (i / 2) * 6 };

			AIStatus zolInfo;
			zolInfo.maxHp = 10;
			zolInfo.dmg = 5;
			zolInfo.speed = 60.0f;
			zolInfo.attackDistance = 2.0f;
			Enemy* zol = new Enemy(L"Zol", zolInfo, AITYPE::MONSTER, AttackType::MELEE_ATTACK, pos, 1.5f, 0.5f);
			AddActor(zol);
		}

		for (int i = 0; i < 2; i++)
		{
			Vec2Int pos = { 5 + (i != 0) * 6, 6 };

			AIStatus batInfo;
			batInfo.maxHp = 10;
			batInfo.dmg = 5;
			batInfo.speed = 40.0f;
			batInfo.attackDistance = 3.0f;
			Enemy* bat = new Enemy(L"Bat", batInfo, AITYPE::MONSTER, AttackType::MELEE_ATTACK, pos, 2.5f, 0.5f);
			AddActor(bat);
		}
		break;

	case 2:
		// oct 4
		for (int i = 0; i < 4; i++)
		{
			Vec2Int pos = { 3 + (i % 2) * 10, 3 + (i / 2) * 6 };
			AIStatus octorokInfo;
			octorokInfo.maxHp = 10;
			octorokInfo.dmg = 5;
			octorokInfo.speed = 50.0f;
			octorokInfo.attackDistance = 3.0f;
			Enemy* octorok = new Enemy(L"Octoroc", octorokInfo, AITYPE::MONSTER, AttackType::RANGED_ATTACK, pos, 2.0f, 10.0f);
			AddActor(octorok);
		}
		break;

	case 3:
		for (int i = 0; i < 2; i++)
		{
			Vec2Int pos = { 3 + (i != 0) * 10, 3 + (i != 0) * 6 };

			AIStatus bow_moblinInfo;
			bow_moblinInfo.maxHp = 10;
			bow_moblinInfo.dmg = 5;
			bow_moblinInfo.speed = 35.0f;
			bow_moblinInfo.attackDistance = 4.0f;
			Enemy* bow_moblin = new Enemy(L"Moblin_A", bow_moblinInfo, AITYPE::MONSTER, AttackType::RANGED_ATTACK, pos, 1.5f, 0.5f);
			AddActor(bow_moblin);
		}

		for (int i = 0; i < 1; i++)
		{
			Vec2Int pos = { 3 + (i == 0) * 10, 3 + (i != 0) * 6 };

			AIStatus spear_moblinInfo;
			spear_moblinInfo.maxHp = 10;
			spear_moblinInfo.dmg = 5;
			spear_moblinInfo.speed = 60.0f;
			spear_moblinInfo.attackDistance = 2.0f;
			Enemy* spear_moblin = new Enemy(L"Moblin_S", spear_moblinInfo, AITYPE::MONSTER, AttackType::MELEE_ATTACK, pos, 1.0f, 0.5f);
			AddActor(spear_moblin);
		}

		break;
	case 4:
		for (int i = 0; i < 2; i++)
		{
			Vec2Int pos = { 3 + (i != 0) * 10, ( i ==0 )? 3 : 10};
			AIStatus darknutInfo;
			darknutInfo.maxHp = 10;
			darknutInfo.dmg = 5;
			darknutInfo.speed = 70.0f;
			darknutInfo.attackDistance = 2.0f;
			Enemy* darknut = new Enemy(L"Darknut", darknutInfo, AITYPE::MONSTER, AttackType::MELEE_ATTACK, pos, 1.5f, 0.5f);
			AddActor(darknut);
		}
		break;
	}
}

void BattleScene::AIClear()
{
	// Enemy
	for (Actor* enemy : _actors[LAYER_MONSTER])
		SAFE_DELETE(enemy);

	_actors[LAYER_MONSTER].clear();

	// Enemy
	for (Actor* hero : _actors[LAYER_HERO])
		SAFE_DELETE(hero);

	_actors[LAYER_HERO].clear();

	// tile
	_tilemapActor = nullptr;

}

bool BattleScene::CanGo(Vec2Int cellPos)
{
	if (_tilemapActor == nullptr)
		return false;

	Tilemap* tm = _tilemapActor->GetTilemap();
	if (tm == nullptr)
		return false;

	Tile* tile = tm->GetTileAt(cellPos);
	if (tile == nullptr)
		return false;

	return tile->value != 0;
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
