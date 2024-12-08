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

		// 시작점
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
		SetCellPos(_path[(_path.size() - 1)], true);
		SetState(AIAniState::ATTACK);
		ResetTarget();
		return;
	}

	if (_pathIndex >= _path.size())
	{
		ResetTarget();
		return;
	}

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_waitTime += deltaTime;
	Vec2Int nextDir = _path[_pathIndex] - _cellPos;

	Vec2Int nextPos = _cellPos + nextDir;

	if (!CanGo(nextPos))
		return;

	if (nextDir.x > 0)
	{
		SetDir(DIR_RIGHT);
		ApplyMovement(DIR_RIGHT);
	}
	else if (nextDir.x < 0)
	{
		SetDir(DIR_LEFT);
		ApplyMovement(DIR_LEFT);
	}
	else if (nextDir.y > 0)
	{
		SetDir(DIR_DOWN);
		ApplyMovement(DIR_DOWN);
	}
	else if (nextDir.y < 0)
	{
		SetDir(DIR_UP);
		ApplyMovement(DIR_UP);
	}

	if (_waitTime >= (_moveTime / 2))
	{
		SetCellPos(nextPos, true);
		_pathIndex++;
		_waitTime = 0;
	}
}

void Enemy::ResetTarget()
{
	_path.clear();
	_arrived = false;
	_pathIndex = 0;
}




void Enemy::HandleMovement(Dir dir)
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	Vec2Int deltaXY[4] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
	Vec2Int nextPos = {  };

	SetDir(dir);
	nextPos = _cellPos + deltaXY[dir];
	if (!CanGo(nextPos))
		return;

	ApplyMovement(dir);

	if (_waitTime >= _moveTime)
	{
		if (nextPos.x != 0 || nextPos.y != 0)
		{
			SetCellPos(nextPos);
			_waitTime = 0;
		}
	}
}

void Enemy::ApplyMovement(Dir dir)
{
	if (dir == DIR_COUNT)
		return;

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	switch (dir)
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
		else if (_target != nullptr && !_arrived)
			CalculateTargetPath();
		else if (_target != nullptr && _arrived)
			ChasingTarget();
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

	if (_attackType == AttackType::MELEE_ATTACK)
	{
		if (GetArroundTarget() && _target != nullptr)
		{
			_target -= _aiInfo.dmg;
			return;
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
