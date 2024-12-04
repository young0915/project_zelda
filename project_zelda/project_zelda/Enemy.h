#pragma once
#include "AI.h"
class Flipbook;

class Enemy : public AI
{
	using Super = AI;
public:
    Enemy(wstring aiName, AIStatus info, AITYPE aiType, AttackType attackType, Vec2Int pos, float movetime);
    ~Enemy();
protected:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	virtual void TickMove() override;
	virtual void TickAttack() override;

	virtual void UpdateAnimation() override;
public:
	int _moveIndex = 0;

private :
	float _moveTime = 0.0f;
	float _waitTime = 0.0f;

	Vec2Int _destPos = {};


	vector<Vec2Int> _patrolRoute;

};

