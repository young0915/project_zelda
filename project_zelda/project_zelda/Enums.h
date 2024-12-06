#pragma once

enum class SceneType
{
	None,
	MainScene,		// �� ó�� ����
	BattleScene,	// ��Ʋ
	EditScene,		// ���� ����
};

enum LAYER_TYPE
{
	LAYER_BACKGROUND,
	LAYER_OBJECT,
	LAYER_AI,
	LAYER_MONSTER,
	LAYER_HERO,
	// ...
	LAYER_UI,

	LAYER_MAXCOUNT
};

enum class ColliderType
{
	Box,
	Sphere,
};

enum COLLISION_LAYER_TYPE : uint8
{
	CLT_OBJECT,
	CLT_GROUND,
	CLT_WALL,
	// ...
};

enum class AITYPE
{
	NONE = 0,
	HERO,
	NPC,
	MONSTER,
	BOSS
};

enum class AIAniState
{
	NONE =0,
	IDLE,
	ATTACK,
	ATTACK_2,
	MOVE,
	DIE,
};

enum class AttackType
{
	NONE = 0,
	MELEE_ATTACK,		// �ٰŸ�.
	RANGED_ATTACK		// ���Ÿ�.
};


enum Dir
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
};

