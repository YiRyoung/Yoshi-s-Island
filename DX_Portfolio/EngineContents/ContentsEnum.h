#pragma once

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
	JUMP,
	STAYUP,
	FALL,
	MAX
};