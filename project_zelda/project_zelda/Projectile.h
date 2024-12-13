#pragma once
#include "FlipbookActor.h"
class BoxCollider;
class AI;

class Projectile : public FlipbookActor
{
	using Super = FlipbookActor;
public:
	Projectile(wstring name, ProjectileInfo info, AITYPE owner);
	~Projectile();
public:
	virtual void BeginPlay() override;
	virtual void Tick() override;
	virtual void Render(HDC hdc) override;

	void SetInfo(Vec2Int initPos, Dir dir, AI* target);

	bool HasExceededRange() const
	{
		return (_pos - _initialPos).LengthSquared() >= _info.selfDestructRange;
	}

public:

	AITYPE _owner;
	AI* _target;
	Dir _dir;
	Vec2Int _cellPos = {};
	Vec2 _initialPos = { 0,0 };
	ProjectileInfo _info;
	// 공격 타입이 원거리형 AI인 경우 
	Flipbook* _flipbookItem[4] = {};
	BoxCollider* _col;
	wstring _name;
	bool _fire = false;

	Dir dirArr[4] = { DIR_UP , DIR_LEFT , DIR_RIGHT , DIR_DOWN };
	wstring strDir[4] = { L"Up", L"Left" , L"Right" , L"Down" };
};

