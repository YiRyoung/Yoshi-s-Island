#include "PreCompile.h"
#include "CrossHair.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

#include "Yoshi.h"
#include "ContentsEnum.h"

ACrossHair::ACrossHair()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;
}

ACrossHair::~ACrossHair()
{
}

void ACrossHair::Init(class AYoshi* _Yoshi)
{
	CrossHairRenderer = CreateDefaultSubObject<USpriteRenderer>();
	CrossHairRenderer->SetupAttachment(RootComponent);
	CrossHairRenderer->SetSprite("YoshiAndMario.png", 135);
	CrossHairRenderer->SetAutoScaleRatio(3.0f);
	AddActorLocation({ 0.0f, 0.0f, static_cast<float>(EOrderNum::HUD) });
}

void ACrossHair::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	StartAngle = StartAngle + Speed * _DeltaTime;

	FVector ParentLocation = GetWorld()->GetMainPawn()->GetActorLocation();

	FVector Offset = FVector::AngleToVectorDeg(StartAngle) * Radius;
	FVector FinalPosition = ParentLocation + Offset;

	SetActorLocation(FinalPosition);
	AddActorLocation({ 0.0f, 0.0f, static_cast<float>(EOrderNum::HUD) });
}