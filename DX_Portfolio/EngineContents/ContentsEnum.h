#pragma once

enum class EOrderNum
{

	HUD = -150,
	PLAYER = -120,
	FRONTBACKGROUND = -100,
	OBJECT = -10,
	COLSTAGE = 10,
	STAGE = 50,
	FOREBACKGROUND = 150,
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
	IDLE,        // 대기
	LOOKUP,      // 위를 쳐다보기
	BEND,        // 숙이기
	WALK,        // 걷기
	RUN,         // 뛰기
	JUMP,        // 점프
	STAYUP,      // 체공
	FALL,        // 낙하
	STICK,       // 혀 내밀기
	EAT,         // 삼키기
	THROW,       // 던지기
	HURT         // 피격
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