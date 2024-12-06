#pragma once

enum class SceneType
{
	None,
	MainScene,		// 맨 처음 시작
	BattleScene,	// 배틀
	EditScene,		// 맵툴 제작
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
	MELEE_ATTACK,		// 근거리.
	RANGED_ATTACK		// 원거리.
};


enum Dir
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
};

