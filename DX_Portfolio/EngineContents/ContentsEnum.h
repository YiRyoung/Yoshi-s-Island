#pragma once

enum class EOrderNum
{

	HUD = -15,
	PLAYER = -12,
	FRONTBACKGROUND = -10,
	OBJECT = -1,
	COLSTAGE = 1,
	STAGE,
	FOREBACKGROUND,
	BACKGROUND,
};

enum class ECheckDir
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NONE
};

enum class EPlayerState
{
	IDLE,
	LOOKUP,
	BEND,
	WALK,
	RUN,
	JUMP,
	STAYUP,
	FALL,
	STICK,
	EAT,
	SPIT,
	THROW,
	HURT
};

enum class EColorType
{
	NONE,
	MAGENTA,
	RED,
	GREEN,
	YELLOW
};

enum class EMonsterState
{
	IDLE,
	WALK,
	ATTACK,
	HURT
};

enum class EShyGuyTypes
{
	GREEN,
	MAGETNTA,
	RED,
	NONE
};