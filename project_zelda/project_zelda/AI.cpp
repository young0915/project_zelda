#include "pch.h"
#include "AI.h"
#include "Enemy.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "BattleScene.h"
#include "ResourceManager.h"

AI::AI(wstring aiName, AIStatus info, AITYPE aiType, AttackType attackType, Vec2Int pos, float attackTime)
	:_aiName(aiName), _aiInfo(info), _aiType(aiType), _attackType(attackType), _cellPos(pos), _attackTime(attackTime)
{
	for (int32 i = 0; i < DIR_COUNT; i++)
		_flipbookMove[dirArr[i]] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Move" + strDir[i] + _aiName);

	for (int32 i = 0; i < DIR_COUNT; i++)
		_flipbookAttack[dirArr[i]] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Attack" + strDir[i] + _aiName);

	_hp = _aiInfo.maxHp;
}

AI::~AI() {}

void AI::BeginPlay()
{
	Super::BeginPlay();
	// TO-DO 방향 설정하기.
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

void AI::TickIdle() {}

void AI::TickMove() {}

void AI::TickAttack(AIAniState state)
{
	if (state == AIAniState::NONE || state == AIAniState::IDLE || state == AIAniState::DIE || state == AIAniState::MOVE || _target == nullptr)
		return;

	float deltatime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_waitAttackTime += deltatime;

	SetState(state);

	if (_waitAttackTime >= _attackTime)
	{
		//SetState(AIAniState::MOVE);
		_waitAttackTime = 0;
	}
}


void AI::SetState(AIAniState state)
{
	if (_state == state)
		return;

	_state = state;
	UpdateAnimation();
}

void AI::UpdateAnimation() {}

void AI::HandleMovement(Dir dir) {}

void AI::SetHp(int hp, bool isHeal)
{
	if (_hp < 0)
	{
		SetState(AIAniState::DIE);
		return;
	}

	if (isHeal)
		_hp += hp;
	else
		_hp -= hp;


}

bool AI::GetArroundTarget()
{
	if (_target == nullptr)
		return false;

	Vec2Int deltaXY[4] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

	for (int32 dir = 0; dir < DIR_COUNT; dir++)
	{
		Vec2Int nextPos = _cellPos + deltaXY[dir];
		if (_target->GetCellPos() == nextPos)
			return true;
	}

	return false;
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

	_destPos = scene->ConvertPos(_cellPos);

	if (teleport)
		_pos = _destPos;
}
