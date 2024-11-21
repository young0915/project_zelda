#include "pch.h"
#include "EditScene.h"

EditScene::EditScene()
{
}

EditScene::~EditScene()
{
}

void EditScene::Init()
{
	Super::Init();


}

void EditScene::Update()
{
	Super::Update();

}

void EditScene::Render(HDC hdc)
{
	Super::Render(hdc);
	Pos pos = { GWinSizeX/2 , GWinSizeY / 2 };
	wstring tile = L"EditScene";
	Utils::DrawTextW(hdc,  pos, tile);

}
