#pragma once

enum class EOrderNum
{
	FRONTBACKGROUND = -20,
	OBSTACLE = -1,
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
	MAX
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
	MAX
};