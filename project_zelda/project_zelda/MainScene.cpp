#include "pch.h"
#include "MainScene.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "SpriteActor.h"
#include "Sprite.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{

	GET_SINGLE(ResourceManager)->LoadTexture(L"Intro", L"Sprite\\UI\\Intro.bmp");
	GET_SINGLE(ResourceManager)->CreateSprite(L"Intro", GET_SINGLE(ResourceManager)->GetTexture(L"Intro"));

	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Intro");

		SpriteActor* background = new SpriteActor();
		background->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);
		const Vec2Int size = sprite->GetSize();
		background->SetPos(Vec2(size.x / 2, size.y / 2));

		AddActor(background);
	}

	Super::Init();

}

void MainScene::Update()
{
	Super::Update();

	// 아무 키 눌러서 입장할 것
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
	{
		GET_SINGLE(SceneManager)->ChangeScene(SceneType::BattleScene);
	}
}

void MainScene::Render(HDC hdc)
{
	Super::Render(hdc);

}