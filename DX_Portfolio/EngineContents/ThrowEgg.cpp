#include "PreCompile.h"
#include "ThrowEgg.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>
#include <EngineCore/TimeEventComponent.h>

#include "ContentsEnum.h"
#include "Yoshi.h"

AThrowEgg::AThrowEgg()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Init();
}

AThrowEgg::~AThrowEgg()
{
}

void AThrowEgg::Init()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetSprite("Eggs.png", 6);
	Renderer->SetAutoScaleRatio(3.0f);

	TimeEvent = CreateDefaultSubObject<UTimeEventComponent>();
}

void AThrowEgg::BeginPlay()
{
	AActor::BeginPlay();

	TimeEvent->AddEvent(5.0f, nullptr, std::bind(&AThrowEgg::DestroyEgg, this), false);
}

void AThrowEgg::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	AddActorLocation(ThrowDir * ThrowSpeed * _DeltaTime);
	ReflectMove(_DeltaTime);
}

void AThrowEgg::ReflectMove(float _DeltaTime)
{
	FVector NextUpPos = GetActorLocation() + ThrowDir * 300.0f * _DeltaTime + FVector{ 0.0f, 22.5f };
	FVector NextDownPos = GetActorLocation() + ThrowDir * 300.0f * _DeltaTime + FVector{ 0.0f, 0.0f };
	FVector NextLeftPos = GetActorLocation() + ThrowDir * 300.0f * _DeltaTime + FVector{ -22.5f, 0.0f };
	FVector NextRightPos = GetActorLocation() + ThrowDir * 300.0f * _DeltaTime + FVector{ 22.5f, 0.0f };

	UColor UpColor = GetWorld()->GetMainPawn<AYoshi>()->GetColor(NextUpPos);
	UColor DownColor = GetWorld()->GetMainPawn<AYoshi>()->GetColor(NextDownPos);
	UColor LeftColor = GetWorld()->GetMainPawn<AYoshi>()->GetColor(NextLeftPos);
	UColor RightColor = GetWorld()->GetMainPawn<AYoshi>()->GetColor(NextRightPos);

	if (UpColor == UColor::MAGENTA || UpColor == UColor::CYAN || UpColor == UColor::GREEN)
	{
		ThrowDir += FVector::DOWN * 2.0f * (-ThrowDir.Dot(FVector::DOWN));
	}
	else if (DownColor == UColor::MAGENTA || DownColor == UColor::CYAN || DownColor == UColor::GREEN)
	{
		ThrowDir += FVector::UP * 2.0f * (-ThrowDir.Dot(FVector::UP));
	}
	else if (LeftColor == UColor::MAGENTA || LeftColor == UColor::CYAN || LeftColor == UColor::GREEN)
	{
		ThrowDir += FVector::RIGHT * 2.0f * (-ThrowDir.Dot(FVector::RIGHT));
	}
	else if (RightColor == UColor::MAGENTA || RightColor == UColor::CYAN || RightColor == UColor::GREEN)
	{
		ThrowDir += FVector::LEFT * 2.0f * (-ThrowDir.Dot(FVector::LEFT));
	}
}

void AThrowEgg::DestroyEgg()
{
	this->Destroy();
}

