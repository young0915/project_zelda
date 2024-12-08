#pragma once
#include "AI.h"

class Enemy : public AI
{
	using Super = AI;
public:
    Enemy(wstring aiName, AIStatus info, AITYPE aiType, AttackType attackType, Vec2Int pos, float movetime, float attackTime);
    ~Enemy();

public:
	void UpdateTarget();
protected:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;
	virtual void TickMove() override;
	virtual void UpdateAnimation() override;
	
public:
	int _moveIndex = 0;

private :
	float _moveTime = 0.0f;

	// TO-DO 공격타임 추가하기
	float _attackTime = 0.0f;
	float _waitTime = 0.0f;

	vector<Vec2Int> _patrolRoute;

};

