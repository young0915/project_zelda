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
    Flipbook* _flipbookMove[4] = {};
    Flipbook* _flipbookAttack[4] = {};

	Dir _dir = DIR_DOWN;

	int _moveIndex = 0;

private :
	float _moveTime = 0.0f;
	float _waitTime = 0.0f;


	// octor, zol, moblin
	// 0
	// {3,3} 
	// {3,5} 
	// {7,3}
	// {7,5}

	// 1
	// {13,3} 
	// {13,5}
	// {10,3} 
	// {10,5}

	// 2
	// {3,9}
	// {3,7}
	// {7,7}
	// {7,9}

	// 3
	// {13,9}
	// {13,7}
	// {10,9}
	// {10,7}

	// bat
	// 0
	// {3,6}
	// {8,6}

	// 1
	// {8,6}
	// {13,6}

	// darknut
	// 0
	// {3,3}
	// {5,3}
	// {3,10}
	// {5,10}

	// 1
	// {13,3}
	// {11,3}
	// {11,10}
	// {13,10}
	vector<Vec2Int> _patrolRoute;

};

