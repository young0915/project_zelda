#include "pch.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "Actor.h"

void CollisionManager::Init(){}

void CollisionManager::Update()
{
	vector<Collider*> collider = _colliders;

	for (int32 i = 0; i < collider.size(); i++)
	{
		for (int32 j = i + 1; j < collider.size(); j++)
		{
			Collider* src = collider[i];
			Collider* dest = collider[j];

			if (src->CheckCollision(dest))
			{
				if (!(src->_collisionMap.contains(dest)))
				{
					src->GetOwner()->OnComponentBeginOverlap(src, dest);
					dest->GetOwner()->OnComponentBeginOverlap(dest, src);
					src->_collisionMap.insert(dest);
					dest->_collisionMap.insert(src);
				}
			}
			else
			{
				if (src->_collisionMap.contains(dest))
				{
					src->GetOwner()->OnComponentEndOverlap(src, dest);
					dest->GetOwner()->OnComponentEndOverlap(dest, src);
					src->_collisionMap.erase(dest);
					dest->_collisionMap.erase(src);
				}
			}
		}
	}
}

void CollisionManager::Clear()
{
	for (int32 i = 0; i < _colliders.size(); i++)
	{
		RemoveCollider(_colliders[i]);
	}
	_colliders.clear();
}

void CollisionManager::AddCollider(Collider* col)
{
	if (col == nullptr)
		return;
	_colliders.push_back(col);
}

void CollisionManager::RemoveCollider(Collider* col)
{
	if (col == nullptr)
		return;

	auto it = std::remove(_colliders.begin(), _colliders.end(), col);
	_colliders.erase(it, _colliders.end());

}