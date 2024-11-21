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
};

