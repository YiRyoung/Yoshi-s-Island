#pragma once

enum class EDirection
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
	LOOKUPSTART,
	LOOKUPEND,
	BENDSTART,
	BENDEND,
	MOVE,
	JUMP,
	MAX
};