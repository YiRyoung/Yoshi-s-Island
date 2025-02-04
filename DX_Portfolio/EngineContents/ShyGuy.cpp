#include "PreCompile.h"
#include "ShyGuy.h"

#include <EngineBase/EngineRandom.h>

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>
#include <EngineCore/TimeEventComponent.h>

#include "Yoshi.h"

AShyGuy::AShyGuy()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	ShyGuyRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ShyGuyRenderer->SetupAttachment(RootComponent);
	ShyGuyRenderer->SetAutoScaleRatio(3.0f);
	ShyGuyRenderer->SetSprite("Shy Guys.png", 0);

	TimeEvent = CreateDefaultSubObject<UTimeEventComponent>();
	SetAnimation();
}

AShyGuy::~AShyGuy()
{
}

void AShyGuy::Init(EShyGuyTypes _CurType)
{
	switch (_CurType)
	{
	case EShyGuyTypes::GREEN:
		ShyGuyRenderer->SetSprite("Shy Guys.png", 0);
		break;
	case EShyGuyTypes::MAGETNTA:
		ShyGuyRenderer->SetSprite("Shy Guys.png", 5);
		break;
	case EShyGuyTypes::RED:
		ShyGuyRenderer->SetSprite("Shy Guys.png", 10);
		break;
	}
	
}

void AShyGuy::BeginPlay()
{
	AMonster::BeginPlay();
	AMonster::MonsterScale = GetActorTransform().Scale;

	Init(CurType);
	SetCollision();
	CreateFSM();
}

void AShyGuy::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
}

void AShyGuy::SetAnimation()
{
	ShyGuyRenderer->CreateAnimation("Green_Walk", "Shy Guys.png", 0, 4, 0.2f);
	ShyGuyRenderer->CreateAnimation("Magenta_Walk", "Shy Guys.png", 5, 9, 0.2f);
	ShyGuyRenderer->CreateAnimation("Red_Walk", "Shy Guys.png", 10, 14, 0.2f);
}

void AShyGuy::SetCollision()
{
	ShyGuyBodyCollision = CreateDefaultSubObject<UCollision>();
	ShyGuyBodyCollision->SetupAttachment(RootComponent);
	ShyGuyBodyCollision->SetCollisionProfileName("MonsterHeadCollision");
	ShyGuyBodyCollision->SetScale3D({ 48.0f , 57 * 0.3f });
	ShyGuyBodyCollision->SetRelativeLocation({ 0.0f, 57 * 0.8f });

	ShyGuyHeadCollision = CreateDefaultSubObject<UCollision>();
	ShyGuyHeadCollision->SetupAttachment(RootComponent);
	ShyGuyHeadCollision->SetCollisionProfileName("MonsterBodyCollision");
	ShyGuyHeadCollision->SetScale3D({ 48.0f, 57 * 0.7f });
	ShyGuyHeadCollision->SetRelativeLocation({ 0.0f, 57 * 0.3f });
}

void AShyGuy::SetCheckCollision()
{

}

void AShyGuy::ChangeAnimDir()
{
	if (CurMonsterState != EMonsterState::IDLE)
	{
		if (TimeEvent != nullptr)
		{
			TimeEvent = nullptr;
			return;
		}
	}

	FVector RotationValue = RootComponent->GetTransformRef().WorldScale;

	if (RotationValue.X > 0)
	{
		RootComponent->SetScale3D({ -1, 1, 1 });
	}
	else if (RotationValue.X < 0)
	{
		RootComponent->SetScale3D({ 1, 1, 1 });
	}

	//TimeEvent->AddEvent(1.0f, nullptr, std::bind(&AShyGuy::ChangeAnimDir, this), false);
}

void AShyGuy::CreateFSM()
{
	FSM.CreateState(EMonsterState::IDLE,
		[this](float _DeltaTime)
		{
			//UEngineRandom Rand;
			//int RandValue = Rand.RandomInt(0, 9);

			//if (RandValue < 6)
			//{
			//	FSM.ChangeState(EMonsterState::WALK);
			//	return;
			//}
		},
		[this]()
		{
			CurMonsterState = EMonsterState::IDLE;

			Init(CurType);
			TimeEvent->AddEvent(1.0f, nullptr, std::bind(&AShyGuy::ChangeAnimDir, this), false);

		});
	
	FSM.CreateState(EMonsterState::WALK,
		[this](float _DeltaTime)
		{
			UEngineRandom Rand;
			int RandValue = Rand.RandomInt(0, 9);

			if (RandValue < 5)
			{
				FSM.ChangeState(EMonsterState::IDLE);
				return;
			}

			float Test = GetActorTransform().Scale.X;

			// LEFT
			if (GetActorTransform().Scale.X > 0.0f)
			{
				AddActorLocation(FVector::LEFT * 100.0f * _DeltaTime);
			}
			else
			{
				AddActorLocation(FVector::RIGHT * 100.0f * _DeltaTime);
			}
		},
		[this]()
		{
			CurMonsterState = EMonsterState::WALK;

			switch (CurType)
			{
			case EShyGuyTypes::GREEN:
				ShyGuyRenderer->ChangeAnimation("Green_Walk");
				break;
			case EShyGuyTypes::MAGETNTA:
				ShyGuyRenderer->ChangeAnimation("Magenta_Walk");
				break;
			case EShyGuyTypes::RED:
				ShyGuyRenderer->ChangeAnimation("Red_Walk");
				break;
			}
		});

	FSM.ChangeState(EMonsterState::IDLE);
}

