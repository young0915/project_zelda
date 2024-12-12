#pragma once
#include "FlipbookActor.h"
class Projectile;
class Flipbook;
class AI;
class BoxCollider;


class AI : public FlipbookActor
{
    using Super = FlipbookActor;
public:
    AI(wstring aiName, AIStatus info, AITYPE aiType, AttackType attackType, Vec2Int Pos, float attackTime);
    ~AI();

protected:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	virtual void TickIdle();
	virtual void TickMove();
	virtual void TickAttack(AIAniState state);
	virtual void SetState(AIAniState state);
	virtual void UpdateAnimation();
	virtual	void HandleMovement(Dir dir);


	void SetDir(Dir dir);
	bool GetArroundTarget();
	bool HasReachedDest();
	bool CanGo(Vec2Int cellPos);
	void SetCellPos(Vec2Int cellPos, bool teleport = false);


public:
	Vec2Int GetCellPos() { return _cellPos; }
	void SetHp(int hp, bool isHeal);

protected:
	Vec2Int _cellPos = {};
	Flipbook* _flipbookMove[4] = {};
	Flipbook* _flipbookAttack[4] = {};

	float _waitAttackTime = 0.0f;
	float _attackTime = 0.0f;

	int _hp = 0;
public:
	// ������ Ÿ��.
	AI* _target = nullptr;
	BoxCollider* _col = nullptr;

	AIAniState _state = AIAniState::NONE;
	AITYPE _aiType = AITYPE::NONE;
	AttackType _attackType = AttackType::NONE;
	wstring _aiName;

	AIStatus _aiInfo;

	Dir _dir = DIR_DOWN;

	Projectile* _projectTile = nullptr;


};

