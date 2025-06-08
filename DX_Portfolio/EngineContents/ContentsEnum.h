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
	IDLE,        // ���
	LOOKUP,      // ���� �Ĵٺ���
	BEND,        // ���̱�
	WALK,        // �ȱ�
	RUN,         // �ٱ�
	JUMP,        // ����
	STAYUP,      // ü��
	FALL,        // ����
	STICK,       // �� ���б�
	EAT,         // ��Ű��
	THROW,       // ������
	HURT         // �ǰ�
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