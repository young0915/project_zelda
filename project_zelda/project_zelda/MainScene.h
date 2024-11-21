#pragma once
#include "Scene.h"
class MainScene : public Scene
{
	using Super = Scene;

public:
	MainScene();
	virtual ~MainScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};

