#include "pch.h"
#include "Enemy.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "BattleScene.h"
#include "SceneManager.h"
#include "Hero.h"


Enemy::Enemy(wstring aiName, AIStatus info, AITYPE aiType, AttackType attackType, Vec2Int pos, float movetime, float attackTime)
	: AI(aiName, info, aiType, attackType, pos, attackTime), _moveTime(movetime)
{
	SetLayer(LAYER_MONSTER);

	// TO-DO 데이터 맞추기.
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
			_patrolRoute.push_back({ 9,5 });
			_patrolRoute.push_back({ 9,3 });
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
			_patrolRoute.push_back({ 9,7 });
			_patrolRoute.push_back({ 9,9 });
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

void Enemy::UpdateTarget()
{
	if (_target != nullptr) {
		// 현재 타겟과의 거리 계산
		Vec2Int dist = (_cellPos - _target->GetCellPos());

		if (dist.Length() <= _aiInfo.attackDistance) {
			// TODO: 공격 로직 (예: TickAttack(AIAniState::ATTACK))
			TickAttack(AIAniState::ATTACK);
			return;
		}
		_target = nullptr;
	}
	else
	{
		// 타겟이 없으면 새 타겟 지정
		BattleScene* scene = dynamic_cast<BattleScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		if (scene == nullptr) {
			return;
		}

		// 모든 영웅 확인
		for (Actor* actor : scene->_actors[LAYER_HERO]) {
			Hero* hero = dynamic_cast<Hero*>(actor);

			if (hero != nullptr) {
				Vec2Int dist = (_cellPos - hero->GetCellPos());
				if (dist.Length() <= _aiInfo.attackDistance) {
					_target = hero;
					break;
				}
			}
		}
	}

	

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
		TickAttack(AIAniState::ATTACK);
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
	UpdateTarget();

	Vec2Int deltaXY[4] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
	Vec2Int nextPos = {  };

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	_waitTime += deltaTime;

	if (_cellPos.x == _patrolRoute[_moveIndex].x && _cellPos.y == _patrolRoute[_moveIndex].y)
	{
		if (_moveIndex < _patrolRoute.size() - 1)
			_moveIndex++;
		else
			_moveIndex = 0;
	}


	if (_cellPos.x == _patrolRoute[_moveIndex].x &&
		_cellPos.y != _patrolRoute[_moveIndex].y)
	{
		if (_cellPos.y > _patrolRoute[_moveIndex].y)
		{
			nextPos = _cellPos + deltaXY[DIR_UP];
			if (CanGo(nextPos))
				_pos.y -= _aiInfo.speed * deltaTime;
		}
		else if (_cellPos.y < _patrolRoute[_moveIndex].y)
		{
			nextPos = _cellPos + deltaXY[DIR_DOWN];
			if (CanGo(nextPos))
				_pos.y += _aiInfo.speed * deltaTime;

		}
	}
	else if (_cellPos.x != _patrolRoute[_moveIndex].x &&
		_cellPos.y == _patrolRoute[_moveIndex].y)
	{

		if (_cellPos.x > _patrolRoute[_moveIndex].x)
		{
			nextPos = _cellPos + deltaXY[DIR_LEFT];
			if (CanGo(nextPos))
				_pos.x -= _aiInfo.speed * deltaTime;
		}
		else if (_cellPos.x < _patrolRoute[_moveIndex].x)
		{
			nextPos = _cellPos + deltaXY[DIR_RIGHT];
			if (CanGo(nextPos))
				_pos.x += _aiInfo.speed * deltaTime;
		}
	}


	if (_waitTime >= _moveTime)
	{
		if (nextPos.x != 0 || nextPos.y != 0)
		{
			SetCellPos(nextPos, true);
			_waitTime = 0;
		}
	}

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
