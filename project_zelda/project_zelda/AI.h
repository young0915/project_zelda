#pragma once
#include "FlipbookActor.h"
class Flipbook;


class AI :  public FlipbookActor
{
	using Super = FlipbookActor;
public:
	AI(wstring aiName, AIInfo info, AITYPE aiType, AttackType attackType, Vec2Int Pos);
	virtual ~AI() override;

	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

private:

	virtual void TickIdle();
	virtual void TickMove();
	virtual void TickSkill();

	void SetState(PlayerState state);
	void SetDir(Dir dir);

	void UpdateAnimation();

	bool HasReachedDest();
	bool CanGo(Vec2Int cellPos);
	void SetCellPos(Vec2Int cellPos, bool teleport = false);

public :
	Flipbook* _flipbookIdle[4] = {};
	Flipbook* _flipbookMove[4] = {};
	Flipbook* _flipbookAttack[4] = {};

	Vec2Int _currentPos = { 0,0 };

	AITYPE _aiType = AITYPE::NONE;
	AttackType _attackType = AttackType::NONE;
	wstring _aiName = nullptr;

	AIInfo _aiInfo;

	Vec2Int _cellPos = {};
	Dir _dir = DIR_DOWN;
	PlayerState _state = PlayerState::Idle;
	bool _keyPressed = false;
};

