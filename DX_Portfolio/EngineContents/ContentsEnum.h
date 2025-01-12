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
	LOOKUPSTART,
	LOOKUPEND,
	BENDSTART,
	BENDEND,
	WALK,
	JUMP,
	MAX
};