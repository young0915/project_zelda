#include "pch.h"
#include "Enemy.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "BattleScene.h"
#include "SceneManager.h"
#include "Hero.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "Projectile.h"


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

	BoxCollider* collider = new BoxCollider();
	_col = collider;
	_col->SetSize({ 50,50 });
	_col->SetShowDebug(false);
	_col->SetCollisionLayer(CLT_ENEMY);
	_col->SetCollisionFlag((1 << CLT_HERO));
	AddComponent(_col);


	_waitMaxAttackTime = (_attackType == AttackType::RANGED_ATTACK && _aiName == L"Octoroc") ? 5.0f : 0.5f;
}

Enemy::~Enemy() {}

void Enemy::UpdateTargetSearch()
{
	BattleScene* scene = dynamic_cast<BattleScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	if (scene == nullptr) {
		return;
	}

	if (scene->_actors[LAYER_HERO].size() > 0)
	{
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

void Enemy::CalculateTargetPath()
{
	Vec2Int start = _cellPos;
	Vec2Int dest = _target->GetCellPos();

	Vec2Int deltaXY[8] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
	int32 cost[] = { 10,10,10,10 };

	int32 size = 20;

	vector<vector<int32>> best(size, vector<int32>(size, INT32_MAX));
	vector<vector<bool>> closed(size, vector<bool>(size, false));
	vector<vector<Vec2Int>> parent(size, vector<Vec2Int>(size, Vec2Int(0, 0)));

	priority_queue<Node, vector<Node>, greater<Node>> pq;

	// 초기값
	{
		int32 g = 0;
		int32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x));

		pq.push(Node(start, g + h, g));
		best[start.y][start.x] = g + h;
		parent[start.y][start.x] = start;
	}

	while (pq.empty() == false)
	{
		Node node = pq.top();
		pq.pop();

		if (closed[node.pos.y][node.pos.x] || best[node.pos.y][node.pos.x] < node.f)
			continue;

		closed[node.pos.y][node.pos.x] = true;

		if (node.pos == dest)
		{
			_arrived = true;
			break;
		}

		for (int32 dir = 0; dir < DIR_COUNT; dir++)
		{
			Vec2Int nextPos = node.pos + deltaXY[dir];
			if (CanGo(nextPos) == false || closed[nextPos.y][nextPos.x])
				continue;

			int32 g = node.g + cost[dir];
			int32 h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));

			if (best[nextPos.y][nextPos.x] <= g + h)
				continue;

			best[nextPos.y][nextPos.x] = g + h;
			pq.push(Node(nextPos, g + h, g));
			parent[nextPos.y][nextPos.x] = node.pos;
		}
	}

	_path.clear();
	Vec2Int pos = dest;

	while (true)
	{
		_path.push_back(pos);

		if (pos == parent[pos.y][pos.x])
			break;

		pos = parent[pos.y][pos.x];
	}

	std::reverse(_path.begin(), _path.end());
}

void Enemy::ChasingTarget()
{
	if (GetArroundTarget())
	{
		SetState(AIAniState::ATTACK);
		return;
	}

	if (!_arrived || _path.empty() || _target == nullptr || GetArroundTarget() || _state == AIAniState::ATTACK || _state == AIAniState::ATTACK_2)
	{
		ResetTarget();
		return;
	}

	if (_cellPos.x == _path[0].x && _cellPos.y == _path[0].y)
		_path.erase(_path.begin());

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_waitTime += deltaTime;

	Vec2Int nextDir = _path[0] - _cellPos;
	Vec2Int nextPos = _cellPos + nextDir;

	if (!CanGo(nextPos))
		return;

	Dir dir = GetDirection(nextDir);

	BattleScene* scene = dynamic_cast<BattleScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	if (scene == nullptr)
		return;

	_destPos = scene->ConvertPos(nextPos);

	_pos.x = MoveToTarget(static_cast<float>(_pos.x), static_cast<float>(_destPos.x), (_aiInfo.speed * deltaTime));
	_pos.y = MoveToTarget(static_cast<float>(_pos.y), static_cast<float>(_destPos.y), (_aiInfo.speed * deltaTime));

	if (_waitTime >= (_moveTime / 2))
	{
		SetDir(dir);
		_waitTime = 0;
		SetCellPos(nextPos, true);
		_path.erase(_path.begin());
	}
}

void Enemy::ResetTarget()
{
	_path.clear();
	_arrived = false;
}

void Enemy::HandleMovement(Dir dir)
{
	Vec2Int deltaXY[4] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
	Vec2Int nextPos = {  };

	SetDir(dir);
	nextPos = _cellPos + deltaXY[dir];
	if (!CanGo(nextPos))
		return;

	MoveTowards(dir);
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
		if (_target == nullptr)
			TickMove();
		else
		{
			if (_attackType == AttackType::MELEE_ATTACK)
			{
				if (!_arrived)
					CalculateTargetPath();
				else if (_arrived)
					ChasingTarget();
			}
			else
			{
				// 플레이어쪽으로 방향 전환

				if (_cellPos.x == _target->GetCellPos().x || _cellPos.y == _target->GetCellPos().y)
				{
					Vec2Int dist = (_cellPos - _target->GetCellPos());
					if (dist.Length() <= _aiInfo.attackDistance)
						SetState(AIAniState::ATTACK);
				}
				else

					_target = nullptr;
			}
		}
		break;
	case AIAniState::DIE:
		BattleScene* scene = dynamic_cast<BattleScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		if (scene == nullptr)
			return;
		scene->RemoveActor(this);
		break;
	}
}

void Enemy::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Enemy::TickAttack(AIAniState state)
{
	Super::TickAttack(state);
	

	if (_target != nullptr)
	{
		Vec2Int dist = (_cellPos - _target->GetCellPos());
		if (dist.Length() > _aiInfo.attackDistance) 
		{
			_target = nullptr;
			SetState(AIAniState::MOVE);
			_arrived = false;
			return;
		}

		Vec2Int attackDir = _cellPos - _target->GetCellPos();
		Dir dir = GetDirection(attackDir);
		// 플레이어에게 방향 두기
		switch (dir)
		{
		case DIR_UP:
			dir = DIR_DOWN;
			break;
		case DIR_DOWN:
			dir = DIR_UP;
			break;
		case DIR_LEFT:
			dir = DIR_RIGHT;
			break;
		case DIR_RIGHT:
			dir = DIR_LEFT;
			break;
		}
		SetDir(dir);

		if (_attackType == AttackType::MELEE_ATTACK)
		{
			if (_target != nullptr && _col->CheckCollision(_target->_col))
			{
				_target->SetHp(_aiInfo.dmg, false);
				return;
			}
		}
		else if (_attackType == AttackType::RANGED_ATTACK)
		{
			float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
			_waitAttackTime += deltaTime;
			
			if (_waitAttackTime >= _waitMaxAttackTime)
			{
				ProjectileInfo info;
				info.dmg = _aiInfo.dmg;
				info.speed = _aiInfo.speed *2;
				info.selfDestructRange = _aiInfo.attackDistance + 2;
				Projectile* projectTile = new Projectile((_aiName == L"Octoroc") ? _aiName : L"Arrow", info, AITYPE::MONSTER);
				projectTile->SetInfo(_cellPos, dir, _target);
				BattleScene* scene = dynamic_cast<BattleScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
				if (scene == nullptr)
					return;
				scene->AddActor(projectTile);
				_waitAttackTime = 0;
				return;
			}
			
		}
	}




}

void Enemy::TickMove()
{
	Super::TickMove();
	UpdateTargetSearch();

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
			HandleMovement(DIR_UP);

		else if (_cellPos.y < _patrolRoute[_moveIndex].y)
			HandleMovement(DIR_DOWN);
	}
	else if (_cellPos.x != _patrolRoute[_moveIndex].x &&
		_cellPos.y == _patrolRoute[_moveIndex].y)
	{

		if (_cellPos.x > _patrolRoute[_moveIndex].x)
			HandleMovement(DIR_LEFT);
		else if (_cellPos.x < _patrolRoute[_moveIndex].x)
			HandleMovement(DIR_RIGHT);
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

void Enemy::MoveTowards(Dir dir)
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_waitTime += deltaTime;

	BattleScene* scene = dynamic_cast<BattleScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	if (scene == nullptr)
		return;

	// 방향에 따른 이동량 계산
	Vec2Int deltaXY[4] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
	Vec2Int nextPos = _cellPos + deltaXY[dir];

	// 목표 위치 설정
	_destPos = scene->ConvertPos(nextPos);

	// 이동 속도 설정
	const float speed = _aiInfo.speed * deltaTime;

	// x 축 이동
	_pos.x = MoveToTarget(static_cast<float>(_pos.x), static_cast<float>(_destPos.x), speed);

	// y 축 이동
	_pos.y = MoveToTarget(static_cast<float>(_pos.y), static_cast<float>(_destPos.y), speed);

	if (_waitTime >= _moveTime)
	{
		SetCellPos(nextPos, true);
		_waitTime = 0;
	}
}

Dir Enemy::GetDirection(Vec2Int nextPos)
{
	if (nextPos.x > 0)
		return DIR_RIGHT;
	else if (nextPos.x < 0)
		return DIR_LEFT;
	else if (nextPos.y > 0)
		return DIR_DOWN;
	else if (nextPos.y < 0)
		return DIR_UP;
}

float Enemy::MoveToTarget(float current, float target, float maxDelta)
{
	if (fabs(current - target) <= maxDelta)
		return target; // 목표 위치에 도달

	return current + (target > current ? maxDelta : -maxDelta); // 현재 위치를 목표로 이동
}
