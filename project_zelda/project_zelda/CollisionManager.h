#pragma once
class Collider;

class CollisionManager
{
	DECLARE_SINGLE(CollisionManager);

public:
	void Init();

	void AddCollider(Collider* col);
	void RemoveCollider(Collider* col);

private:
	vector<Collider*> _colliders;
};

