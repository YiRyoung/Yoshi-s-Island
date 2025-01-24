#include "PreCompile.h"
#include "Egg.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>

#include "ContentsEnum.h"
#include "Yoshi.h"

AEgg::AEgg()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Init();
}

AEgg::~AEgg()
{
}

void AEgg::Init()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetSprite("Eggs.png", 6);
	Renderer->SetAutoScaleRatio(3.0f);
}

void AEgg::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	AddActorLocation(ThrowDir * 300.0f * _DeltaTime);

	FVector NextPos = GetActorLocation() + ThrowDir * 300.0f * _DeltaTime + FVector{ 0.0f,  22.5f};
	UColor Color = GetWorld()->GetMainPawn<AYoshi>()->GetColor(NextPos);
	if (Color.operator==(UColor::MAGENTA))
	{
		int a = 0;
	}
}

