#include "pch.h"
#include "AI.h"
#include "Enemy.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "BattleScene.h"

AI::AI(wstring aiName, AIStatus info, AITYPE aiType, AttackType attackType, Vec2Int pos) 
	:_aiName(aiName), _aiInfo(info), _aiType(aiType),_attackType(attackType), _cellPos(pos)
{
}

AI::~AI()
{
}

void AI::BeginPlay()
{
	Super::BeginPlay();
	SetDir(DIR_DOWN);
	SetCellPos(_cellPos, true);
}

void AI::Tick()
{
	Super::Tick();
}

void AI::Render(HDC hdc)
{
	Super::Render(hdc);
}

void AI::TickIdle()
{
}

void AI::TickMove()
{
	
}

void AI::TickAttack()
{
}

void AI::SetState(AIAniState state)
{
	if (_state == state)
		return;

	_state = state;
	UpdateAnimation();
}

void AI::UpdateAnimation()
{
}

void AI::SetDir(Dir dir)
{
	_dir = dir;
	UpdateAnimation();
}

bool AI::HasReachedDest()
{
	Vec2 dir = (_destPos - _pos);
	return (dir.Length() < 10.f);
}

bool AI::CanGo(Vec2Int cellPos)
{
	BattleScene* scene = dynamic_cast<BattleScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	if (scene == nullptr)
		return false;

	return scene->CanGo(cellPos);
}

void AI::SetCellPos(Vec2Int cellPos, bool teleport)
{
	_cellPos = cellPos;

	BattleScene* scene = dynamic_cast<BattleScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	if (scene == nullptr)
		return;

	_destPos = scene->ConvertPos(cellPos);

	if (teleport)
		_pos = _destPos;
}
