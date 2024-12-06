#include "pch.h"
#include "Hero.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"

Hero::Hero(wstring aiName, AIStatus info, AITYPE aiType, AttackType attackType, Vec2Int pos, float attackTime) : AI(aiName, info, aiType, attackType, pos, attackTime)
{
	_flipbookIdle[DIR_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_IdleUp_" + _aiName);
	_flipbookIdle[DIR_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_IdleDown_" + _aiName);
	_flipbookIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_IdleLeft_" + _aiName);
	_flipbookIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_IdleRight_" + _aiName);

	_flipbookAttackBow[DIR_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AttackBowUp_" + _aiName);
	_flipbookAttackBow[DIR_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AttackBowDown_" + _aiName);
	_flipbookAttackBow[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AttackBowLeft_" + _aiName);
	_flipbookAttackBow[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AttackBowRight_" + _aiName);

	SetLayer(LAYER_HERO);
}

Hero::~Hero()
{
}

void Hero::BeginPlay()
{
	Super::BeginPlay();
	SetDir(DIR_DOWN);
	SetState(AIAniState::IDLE);
}

void Hero::Tick()
{
	Super::Tick();

	switch (_state)
	{
	case AIAniState::IDLE:
		TickIdle();
		break;
	case AIAniState::ATTACK:
		TickAttack(AIAniState::ATTACK);
		break;
	case AIAniState::ATTACK_2:
		TickAttack(AIAniState::ATTACK_2);
		break;
	case AIAniState::MOVE:
		TickMove();
		break;
	}
}

void Hero::Render(HDC hdc)
{
	Super::Render(hdc);

}

void Hero::TickIdle()
{
	Super::TickIdle();
	_keyPressed = true;

	if (GET_SINGLE(InputManager)->GetButton(KeyType::Up))
		SetMove(DIR_UP);
	else  if (GET_SINGLE(InputManager)->GetButton(KeyType::Down))
		SetMove(DIR_DOWN);
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::Left))
		SetMove(DIR_LEFT);
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::Right))
		SetMove(DIR_RIGHT);
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::Z))
		TickAttack(AIAniState::ATTACK);
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::X))
	{
		SetState(AIAniState::ATTACK_2);
	}
	else
	{
		_keyPressed = false;
		if (_state == AIAniState::IDLE)
			UpdateAnimation();
	}

}

void Hero::TickMove()
{
	Super::TickMove();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	Vec2 dir = (_destPos - _pos);
	if (dir.Length() < 10.f)
	{
		SetState(AIAniState::IDLE);
		_pos = _destPos;
	}
	else
	{
		switch (_dir)
		{
		case DIR_UP:
			_pos.y -= _aiInfo.speed * deltaTime;
			break;
		case DIR_DOWN:
			_pos.y += _aiInfo.speed * deltaTime;
			break;
		case DIR_LEFT:
			_pos.x -= _aiInfo.speed * deltaTime;
			break;
		case DIR_RIGHT:
			_pos.x += _aiInfo.speed * deltaTime;
			break;
		}
	}
}

void Hero::UpdateAnimation()
{
	Super::UpdateAnimation();
	switch (_state)
	{
	case AIAniState::IDLE:
		SetFlipbook(_flipbookIdle[_dir]);
		break;
	case AIAniState::ATTACK:
		SetFlipbook(_flipbookAttack[_dir]);
		break;
	case AIAniState::ATTACK_2:
		SetFlipbook(_flipbookAttackBow[_dir]);
		break;
	case AIAniState::MOVE:
		SetFlipbook(_flipbookMove[_dir]);
		break;
	}

}

void Hero::SetMove(Dir dir)
{
	Vec2Int deltaXY[4] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

	SetDir(dir);
	Vec2Int nextPos = _cellPos + deltaXY[_dir];
	if (CanGo(nextPos))
	{
		SetCellPos(nextPos);
		SetState(AIAniState::MOVE);
	}
}
