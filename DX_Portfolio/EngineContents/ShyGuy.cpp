#include "PreCompile.h"
#include "ShyGuy.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/TimeEventComponent.h>

AShyGuy::AShyGuy()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetAutoScaleRatio(3.0f);
	Renderer->SetSprite("Shy Guys.png", 0);

	TimeEvent = CreateDefaultSubObject<UTimeEventComponent>();
}

AShyGuy::~AShyGuy()
{
}

void AShyGuy::BeginPlay()
{
	AMonster::BeginPlay();
	ChangeState(EMonsterState::IDLE);
}

void AShyGuy::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);
}

void AShyGuy::SetAnimation()
{
	Renderer->SetSprite("Shy Guys.png", 0);
	Renderer->CreateAnimation("Walk", "Shy Guys.png", 0, 5, 0.7f);
	Renderer->ChangeAnimation("Walk");
}

void AShyGuy::ChangeIdleAnim()
{
	FVector RotationValue = RootComponent->GetTransformRef().WorldScale;

	if (RotationValue.X > 0)
	{
		RootComponent->SetScale3D({ -1, 1, 1 });
	}
	else if (RotationValue.X < 0)
	{
		RootComponent->SetScale3D({ 1, 1, 1 });
	}

	TimeEvent->AddEvent(1.0f, nullptr, std::bind(&AShyGuy::ChangeIdleAnim, this), false);

}

void AShyGuy::SetIdleAnim()
{
}

void AShyGuy::IdleStart()
{
	 TimeEvent->AddEvent(1.0f, nullptr, std::bind(&AShyGuy::ChangeIdleAnim, this), false);

	SetIdleAnim();
}

void AShyGuy::Idle(float _DeltaTime)
{
	AMonster::Idle(_DeltaTime);
}