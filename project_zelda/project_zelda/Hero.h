#pragma once
#include "AI.h"
class Flipbook;

class Hero :
	public AI
{
	using Super = AI;
public:
	Hero(wstring aiName, AIStatus info, AITYPE aiType, AttackType attackType, Vec2Int pos);
	~Hero();

protected:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	virtual void TickIdle() override;
	virtual void TickMove() override;
	virtual void TickAttack() override;

	virtual void UpdateAnimation() override;

public:
	void SetMove(Dir dir);
public:

	Flipbook* _flipbookIdle[4] = {};
	float _waitTime = 0.0f;

	bool _keyPressed = false;
};
