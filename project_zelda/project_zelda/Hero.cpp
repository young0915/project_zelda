#include "pch.h"
#include "Hero.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"

Hero::Hero(wstring aiName, AIStatus info, AITYPE aiType, AttackType attackType, Vec2Int pos) : AI(aiName, info, aiType, attackType, pos)
{
	_flipbookIdle[DIR_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_IdleUp_" + _aiName);
	_flipbookIdle[DIR_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_IdleDown_" + _aiName);
	_flipbookIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_IdleLeft_" + _aiName);
	_flipbookIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_IdleRight_" + _aiName);


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
		TickAttack();
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

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
		SetMove(DIR_UP);
	else  if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
		SetMove(DIR_DOWN);
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
		SetMove(DIR_LEFT);

	else if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
		SetMove(DIR_RIGHT);
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

void Hero::TickAttack()
{
	Super::TickAttack();

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
