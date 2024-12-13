#include "pch.h"
#include "Projectile.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "BoxCollider.h"
#include "AI.h"
#include "BattleScene.h"
#include "SceneManager.h"


Projectile::Projectile(wstring name, ProjectileInfo info, AITYPE owner) : _name(name), _info(info), _owner(owner)
{
	_flipbookItem[DIR_UP] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_" + _name + L"_Item");
	_flipbookItem[DIR_DOWN] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_" + _name + L"_Item");
	_flipbookItem[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_" + _name + L"_Item");
	_flipbookItem[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetFlipbook(L"FB_" + _name + L"_Item");

	BoxCollider* collider = new BoxCollider();
	_col = collider;
	_col->SetSize({ 40,40 });
	_col->SetShowDebug(false);
	_col->SetCollisionLayer(CLT_PROJECTILE);

	switch (_owner)
	{
	case AITYPE::HERO:
		_col->SetCollisionFlag(1 << CLT_PROJECTILE);
		break;
	case AITYPE::MONSTER:
		_col->SetCollisionFlag((1 << CLT_HERO));
		break;
	}
	SetLayer(LAYER_OBJECT);
	AddComponent(_col);
}

Projectile::~Projectile() {}

void Projectile::BeginPlay()
{
	Super::BeginPlay();
}

void Projectile::Tick()
{
	Super::Tick();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	switch (_dir)
	{
	case DIR_UP:
		_pos.y -= _info.speed * deltaTime;

		break;
	case DIR_DOWN:
		_pos.y += _info.speed * deltaTime;
		break;
	case DIR_LEFT:
		_pos.x -= _info.speed * deltaTime;
		break;
	case DIR_RIGHT:
		_pos.x += _info.speed * deltaTime;
		break;
	}

	if (_target != nullptr && _col->CheckCollision(_target->_col))
	{
		_target->SetHp(_info.dmg, false);
		BattleScene* scene = dynamic_cast<BattleScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
		if (scene == nullptr)
			return;
		scene->RemoveActor(this);

		return;
	}
	SetFlipbook(_flipbookItem[_dir]);
}

void Projectile::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Projectile::SetInfo(Vec2Int initPos, Dir dir, AI* target)
{
	BattleScene* scene = dynamic_cast<BattleScene*>(GET_SINGLE(SceneManager)->GetCurrentScene());
	if (scene == nullptr)
		return;
	_initialPos = scene->ConvertPos(initPos);
	_pos = _initialPos;
	_destPos = _pos;
	_dir = dir;
	_target = target;
	_fire = true;
}
