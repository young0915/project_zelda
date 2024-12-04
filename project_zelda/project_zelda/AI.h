#pragma once
#include "FlipbookActor.h"


class AI :
    public FlipbookActor
{
    using Super = FlipbookActor;
public:
    AI(wstring aiName, AIStatus info, AITYPE aiType, AttackType attackType, Vec2Int Pos);
    ~AI();

protected:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	virtual void TickIdle();
	virtual void TickMove();
	virtual void TickAttack();

	virtual void SetState(AIAniState state);

	virtual void UpdateAnimation();

	void SetDir(Dir dir);

	bool HasReachedDest();
	bool CanGo(Vec2Int cellPos);
	void SetCellPos(Vec2Int cellPos, bool teleport = false);


protected:
	Vec2Int _cellPos = {};
	Flipbook* _flipbookMove[4] = {};
	Flipbook* _flipbookAttack[4] = {};


public:

	AIAniState _state = AIAniState::NONE;
	AITYPE _aiType = AITYPE::NONE;
	AttackType _attackType = AttackType::NONE;
	wstring _aiName;

	AIStatus _aiInfo;

	Dir _dir = DIR_DOWN;

};

