#include "pch.h"
#include "Hero.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "BoxCollider.h"
#include "BattleScene.h"
#include "SceneManager.h"
#include "Enemy.h"

Hero::Hero(wstring aiName, AIStatus info, AITYPE aiType, AttackType attackType, Vec2Int pos, float attackTime) : AI(aiName, info, aiType, attackType, pos, attackTime)
{
	for (int32 i = 0; i < DIR_COUNT; i++)
		_flipbookIdle[dirArr[i]] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_Idle" + strDir[i] + _aiName);

	for (int32 i = 0; i < DIR_COUNT; i++)
		_flipbookAttackBow[dirArr[i]] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_AttackBow" + strDir[i] + _aiName);


	BoxCollider* collider = new BoxCollider();
	_col = collider;
	_col->SetSize({ 70,70 });
	_col->SetShowDebug(false);
	AddComponent(_col);
	_col->SetCollisionLayer(CLT_HERO);
	_col->SetCollisionFlag((1 << CLT_ENEMY) | (1 << CLT_PROJECTILE));

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
	case AIAniState::DIE:
		BattleScene* scene = dynamic_cast<BattleScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		if (scene == nullptr)
			return;
		scene->RemoveActor(this);

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
		HandleMovement(DIR_UP);
	else  if (GET_SINGLE(InputManager)->GetButton(KeyType::Down))
		HandleMovement(DIR_DOWN);
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::Left))
		HandleMovement(DIR_LEFT);
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::Right))
		HandleMovement(DIR_RIGHT);
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::Z))
		TickAttack(AIAniState::ATTACK);
	else if (GET_SINGLE(InputManager)->GetButton(KeyType::X))
		SetState(AIAniState::ATTACK_2);
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

void Hero::TickAttack(AIAniState state)
{
	float deltatime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_waitAttackTime += deltatime;

	SetState(state);


	if (_waitAttackTime >= _attackTime)
	{
		SetState(AIAniState::MOVE);

		_waitAttackTime = 0;
	}

	BattleScene* scene = dynamic_cast<BattleScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	if (scene == nullptr)
		return;

	if (scene->_actors[LAYER_MONSTER].size() > 0)
	{
		// ��� ���� Ȯ��
		for (Actor* actor : scene->_actors[LAYER_MONSTER]) {
			Enemy* enemy = dynamic_cast<Enemy*>(actor);

			if (enemy != nullptr) {
				Vec2Int dist = (_cellPos - enemy->GetCellPos());
				if (dist.Length() <= _aiInfo.attackDistance) {
					_target = enemy;
					break;
				}
			}
		}
	}

	if (_target != nullptr && _col->CheckCollision(_target->_col))
	{
		_target->SetHp(_aiInfo.dmg, false);
		_target = nullptr;
		return;
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

void Hero::HandleMovement(Dir dir)
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
