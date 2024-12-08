#pragma once
#include "AI.h"
class Flipbook;

class Hero :
	public AI
{
	using Super = AI;
public:
	Hero(wstring aiName, AIStatus info, AITYPE aiType, AttackType attackType, Vec2Int pos, float attackTime);
	~Hero();

protected:
	virtual void BeginPlay() override;
	virtual void Render(HDC hdc) override;
	virtual void Tick() override;

	virtual void TickIdle() override;
	virtual void TickMove() override;

	virtual void UpdateAnimation() override;
	virtual void HandleMovement(Dir dir) override;
public:
public:

	Flipbook* _flipbookIdle[4] = {};
	Flipbook* _flipbookAttackBow[4] = {};
	bool _keyPressed = false;
};

