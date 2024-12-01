#pragma once
#include "Scene.h"

class Actor;
class UI;

class EditScene : public Scene
{
	using Super = Scene;

public:
	EditScene();
	virtual ~EditScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	void OnClickedTileButton(int index);

	class TilemapActor* _tilemapActor = nullptr;
};

