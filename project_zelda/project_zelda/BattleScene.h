#pragma once
#include "Scene.h"
class BattleScene : public Scene
{
	using Super = Scene;

public:
	BattleScene();
	virtual ~BattleScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void LoadResource(int stage);
	void SetStage(int stage);
	void SpawnEnemy(int stage);
	void AIClear();

	bool CanGo(Vec2Int cellPos);
	Vec2 ConvertPos(Vec2Int cellPos);


public:
	class TilemapActor* _tilemapActor = nullptr;
	bool _init = false;
	int _stageIndex = 1;

};

