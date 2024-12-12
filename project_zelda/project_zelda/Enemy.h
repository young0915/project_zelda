#pragma once
#include "AI.h"
class AI;

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
	void MoveTowards(Dir dir);
	Dir GetDirection(Vec2Int nextPos);
	float MoveToTarget(float current, float target, float maxDelta);

protected:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;
	virtual void TickAttack(AIAniState state) override;
	virtual void TickMove() override;
	virtual void UpdateAnimation() override;
	virtual void HandleMovement(Dir dir) override;

public:
	int _moveIndex = 0;

private :
	float _moveTime = 0.0f;

	float _attackTime = 0.0f;
	float _waitTime = 0.0f;
	bool _arrived = false;
	vector<Vec2Int> _patrolRoute;
	vector<Vec2Int> _path;



};

