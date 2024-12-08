#pragma once
#include "AI.h"

class Enemy : public AI
{
	using Super = AI;
public:
    Enemy(wstring aiName, AIStatus info, AITYPE aiType, AttackType attackType, Vec2Int pos, float movetime, float attackTime);
    ~Enemy();

public:
	void UpdateTargetSearch();
	void CalculateTargetPath();
	void ChasingTarget();
	void ResetTarget();

	bool GetArroundHero();

protected:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;
	virtual void TickMove() override;
	virtual void UpdateAnimation() override;
	virtual void HandleMovement(Dir dir) override;
	virtual void ApplyMovement(Dir dir);

public:
	int _moveIndex = 0;

private :
	float _moveTime = 0.0f;

	float _attackTime = 0.0f;
	float _waitTime = 0.0f;
	bool _arrived = false;
	vector<Vec2Int> _patrolRoute;
	vector<Vec2Int> _path;

	int32 _pathIndex = 1;

};

