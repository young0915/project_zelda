#include "pch.h"
#include "Actor.h"
#include "Component.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "AI.h"

Actor::Actor()
{

}

Actor::~Actor()
{
	for (Component* component : _components)
		SAFE_DELETE(component);
}

void Actor::BeginPlay()
{
	for (Component* component : _components)
	{
		component->BeginPlay();
	}
}

void Actor::Tick()
{
	for (Component* component : _components)
	{
		component->TickComponent();
	}
}

void Actor::Render(HDC hdc)
{
	for (Component* component : _components)
	{
		component->Render(hdc);
	}
}

void Actor::AddComponent(Component* component)
{
	if (component == nullptr)
		return;

	Collider* col = dynamic_cast<Collider*>(component);
	if (col != nullptr)
		GET_SINGLE(CollisionManager)->AddCollider(col);

	component->SetOwner(this);



	
	_components.push_back(component);
}

void Actor::RemoveComponent(Component* component)
{
	auto findIt = std::find(_components.begin(), _components.end(), component);
	if (findIt == _components.end())
		return;

	Collider* col = dynamic_cast<Collider*>(component);
	if (col != nullptr)
		GET_SINGLE(CollisionManager)->RemoveCollider(col);

	_components.erase(findIt);
}

Component* Actor::GetCollider()
{
	for (Component* component : _components)
	{
		if (dynamic_cast<Collider*>(component))
			return component;
	}

	return nullptr;
}

void Actor::OnComponentBeginOverlap(Collider* collider, Collider* other)
{
	AI* ai = dynamic_cast<AI*>(other);
	AI* ai_me = dynamic_cast<AI*>(collider);

	if (ai_me != nullptr && ai_me->_state == AIAniState::ATTACK)
	{
		ai_me;
	}
}

void Actor::OnComponentEndOverlap(Collider* collider, Collider* other)
{
	AI* ai = dynamic_cast<AI*>(other);
	AI* ai_me = dynamic_cast<AI*>(collider);

	if (ai_me != nullptr && ai_me->_state == AIAniState::ATTACK)
	{
		ai_me;
	}
}
