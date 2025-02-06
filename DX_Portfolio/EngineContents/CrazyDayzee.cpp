#include "PreCompile.h"
#include "CrazyDayzee.h"

#include <EngineBase/EngineRandom.h>

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>

ACrazyDayzee::ACrazyDayzee()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Init();
	SetAnimation();
	SetCollision();
	CreateMonsterFSM();
}

ACrazyDayzee::~ACrazyDayzee()
{
}

void ACrazyDayzee::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	MonsterFSM.Update(_DeltaTime);
	SetCollisionLink(_DeltaTime);
}

void ACrazyDayzee::CreateMonsterFSM()
{
	MonsterFSM.CreateState(EMonsterState::IDLE,
		[this](float _DeltaTime)
		{
			UEngineRandom Random;
			int Rand = Random.RandomInt(0, 9);
			
			if (Rand < 6)
			{
				MonsterFSM.ChangeState(EMonsterState::WALK);
				return;
			}
		},
		[this]()
		{
			Renderer->ChangeAnimation("Idle");
		});

	MonsterFSM.CreateState(EMonsterState::WALK,
		[this](float _DeltaTime)
		{
			UEngineRandom Rand;
			int RandNum = Rand.RandomInt(0, 9);
			if (RandNum < 3)
			{
				MonsterFSM.ChangeState(EMonsterState::IDLE);
				return;
			}

			float ScaleX = GetActorTransform().Scale.X;
			if (ScaleX > 0.0f && CheckPointColor(ECheckDir::LEFT, UColor::BLACK))
			{
				AddActorLocation(FVector::LEFT * 40.0f * _DeltaTime);
			}
			else if (!CheckPointColor(ECheckDir::LEFT, UColor::BLACK))
			{
				RootComponent->SetScale3D({ -1.0f, 1.0f, 1.0f });
			}

			if (ScaleX < 0.0f && CheckPointColor(ECheckDir::RIGHT, UColor::BLACK))
			{
				AddActorLocation(FVector::RIGHT * 40.0f * _DeltaTime);
			}
			else if (!CheckPointColor(ECheckDir::RIGHT, UColor::BLACK))
			{
				RootComponent->SetScale3D({ 1.0f, 1.0f, 1.0f });
			}

		},
		[this]()
		{
			Renderer->ChangeAnimation("Walk");
		});

	MonsterFSM.ChangeState(EMonsterState::IDLE);
	return;
}

void ACrazyDayzee::Init()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetAutoScaleRatio(3.0f);
	Renderer->SetSprite("CrazyDazee.png", 10);
}

void ACrazyDayzee::SetAnimation()
{
	Renderer->CreateAnimation("Idle", "CrazyDazee.png", 0, 0);
	Renderer->CreateAnimation("Walk", "CrazyDazee.png", 0, 9, 0.1f);
}

void ACrazyDayzee::SetCollision()
{
	HeadCollision = CreateDefaultSubObject<UCollision>();
	HeadCollision->SetupAttachment(RootComponent);
	HeadCollision->SetCollisionProfileName("MonsterHeadCollision");
	HeadCollision->SetScale3D({ 63.0f , 10.0f });
	HeadCollision->SetRelativeLocation({ 0.0f, 75.0f });

	BodyCollision = CreateDefaultSubObject<UCollision>();
	BodyCollision->SetupAttachment(RootComponent);
	BodyCollision->SetCollisionProfileName("MonsterBodyCollision");
	BodyCollision->SetScale3D({ 63.0f , 75.0f * 0.9f });
	BodyCollision->SetRelativeLocation({ 0.0f, 75.0f * 0.5f });
}

void ACrazyDayzee::SetCollisionLink(float _DeltaTime)
{
	std::vector<UCollision*> FootCollisions;
	if (HeadCollision->CollisionCheck("FootCollision", FootCollisions))
	{
		IsStepped = true;
	}

	if (IsStepped)
	{
		AMonster::FallDown(_DeltaTime);
	}
}