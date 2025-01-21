#include "PreCompile.h"
#include "Monster.h"

#include <EngineCore/Collision.h>

AMonster::AMonster()
{
}

AMonster::~AMonster()
{
}

void AMonster::BeginPlay()
{
	AActor::BeginPlay();
}

void AMonster::ChangeState(EMonsterState _CurMonsterState)
{
	CurMonsterState = _CurMonsterState;

	switch (CurMonsterState)
	{
	case EMonsterState::IDLE:
		IdleStart();
		break;
	case EMonsterState::WALK:
		WalkStart();
		break;
	case EMonsterState::ATTACK:
		AttackStart();
		break;
	case EMonsterState::HURT:
		HurtStart();
		break;
	default:
		break;
	}
}

void AMonster::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	MosnterFSM(_DeltaTime);
}

void AMonster::SetAnimation()
{
}

void AMonster::SetCollision()
{
	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("MonsterCollision");
	Collision->SetScale3D({ MonsterScale.X, MonsterScale.Y });
	Collision->SetRelativeLocation({ 0.0f, MonsterScale.Y });
}

void AMonster::MosnterFSM(float _DeltaTime)
{
	switch (CurMonsterState)
	{
	case EMonsterState::IDLE:
		Idle(_DeltaTime);
		break;
	case EMonsterState::WALK:
		Walk(_DeltaTime);
		break;
	case EMonsterState::ATTACK:
		Attack(_DeltaTime);
		break;
	case EMonsterState::HURT:
		Hurt(_DeltaTime);
		break;
	}
}

void AMonster::Gravity(float _DeltaTime)
{
}

void AMonster::IdleStart()
{
}

void AMonster::Idle(float _DeltaTime)
{
}

void AMonster::WalkStart()
{
}

void AMonster::Walk(float _DeltaTime)
{
}

void AMonster::AttackStart()
{
}

void AMonster::Attack(float _DeltaTime)
{
}

void AMonster::HurtStart()
{
}

void AMonster::Hurt(float _DeltaTime)
{
}