#include "pch.h"
#include "Enemy.h"
#include "ResourceManager.h"
#include "TimeManager.h"


Enemy::Enemy(wstring aiName, AIStatus info, AITYPE aiType, AttackType attackType, Vec2Int pos, float movetime)
	: AI(aiName, info, aiType, attackType, pos), _moveTime(movetime)
{
	_flipbookMove[DIR_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveUp_" + _aiName);
	_flipbookMove[DIR_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveDown_" + _aiName);
	_flipbookMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveLeft_" + _aiName);
	_flipbookMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_MoveRight_" + _aiName);

	_flipbookAttack[DIR_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AttackUp_" + _aiName);
	_flipbookAttack[DIR_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AttackDown_" + _aiName);
	_flipbookAttack[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AttackLeft_" + _aiName);
	_flipbookAttack[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AttackRight_" + _aiName);

	SetLayer(LAYER_MONSTER);

	// // octor, zol, moblin
	if (_aiName == L"Zol" || _aiName == L"Octoroc" || _aiName == L"Moblin_S" || _aiName == L"Moblin_A")
	{
		if ((pos.x == 3 && pos.y == 3))
		{
			_patrolRoute.push_back({ 3,3 });
			_patrolRoute.push_back({ 3,5 });
			_patrolRoute.push_back({ 7,5 });
			_patrolRoute.push_back({ 7,3 });
		}
		else if (pos.x == 13 && pos.y == 3)
		{
			_patrolRoute.push_back({ 13,3 });
			_patrolRoute.push_back({ 13,5 });
			_patrolRoute.push_back({ 10,5 });
			_patrolRoute.push_back({ 10,3 });
		}
		else if (pos.x == 3 && pos.y == 9)
		{
			_patrolRoute.push_back({ 3,9 });
			_patrolRoute.push_back({ 3,7 });
			_patrolRoute.push_back({ 7,7 });
			_patrolRoute.push_back({ 7,9 });
		}
		else
		{
			_patrolRoute.push_back({ 13,9 });
			_patrolRoute.push_back({ 13,7 });
			_patrolRoute.push_back({ 10,7 });
			_patrolRoute.push_back({ 10,9 });
		}
	}
	else if (_aiName == L"Bat")
	{
		if (pos.x == 5 && pos.y == 6)
		{
			_patrolRoute.push_back({ 3,6 });
			_patrolRoute.push_back({ 8,6 });
		}
		else
		{
			_patrolRoute.push_back({ 8,6 });
			_patrolRoute.push_back({ 13, 6 });
		}

	}
	else if (_aiName == L"Darknut")
	{
		if (pos.x == 3 && pos.y == 6)
		{
			_patrolRoute.push_back({ 3, 3 });
			_patrolRoute.push_back({ 5, 3 });
			_patrolRoute.push_back({ 3, 10 });
			_patrolRoute.push_back({ 5, 10 });
		}
		else
		{
			_patrolRoute.push_back({ 13,3 });
			_patrolRoute.push_back({ 11,3 });
			_patrolRoute.push_back({ 11,10 });
			_patrolRoute.push_back({ 13,10 });
		}
	}

}

Enemy::~Enemy()
{
}

void Enemy::BeginPlay()
{
	Super::BeginPlay();
	SetDir(DIR_DOWN);
	SetState(AIAniState::MOVE);
}

void Enemy::Tick()
{
	Super::Tick();

	switch (_state)
	{
	case AIAniState::ATTACK:
		TickAttack();
		break;
	case AIAniState::MOVE:
		TickMove();
		break;
	}
}

void Enemy::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Enemy::TickMove()
{
	Super::TickMove();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	_waitTime += deltaTime;

	if (_waitTime >= _moveTime)
	{
		_cellPos = _patrolRoute[_moveIndex];
		SetCellPos(_cellPos, true);

		if (_moveIndex < _patrolRoute.size() - 1) 
			_moveIndex++;
		else 
			_moveIndex = 0;

		_waitTime = 0;
	}
	

	//switch (_dir)
	//{
	//case DIR_UP:
	//	_pos.y -= _aiInfo.speed * deltaTime;
	//	break;
	//case DIR_DOWN:
	//	_pos.y += _aiInfo.speed * deltaTime;
	//	break;
	//case DIR_LEFT:
	//	_pos.x -= _aiInfo.speed * deltaTime;
	//	break;
	//case DIR_RIGHT:
	//	_pos.x += _aiInfo.speed * deltaTime;
	//	break;
	//}

}

void Enemy::TickAttack()
{
	Super::TickAttack();

}



void Enemy::UpdateAnimation()
{
	Super::UpdateAnimation();
	switch (_state)
	{
	case AIAniState::ATTACK:
		SetFlipbook(_flipbookAttack[_dir]);
		break;
	case AIAniState::MOVE:
		SetFlipbook(_flipbookMove[_dir]);
		break;
	}
}
