#include "PreCompile.h"
#include "CrossHair.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

#include "ContentsEnum.h"
#include "Yoshi.h"

ACrossHair::ACrossHair()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;
}

ACrossHair::~ACrossHair()
{
}

void ACrossHair::InitCrossHair(class AYoshi* _Yoshi)
{
	CrossHairRenderer = CreateDefaultSubObject<USpriteRenderer>();
	CrossHairRenderer->SetupAttachment(RootComponent);
	CrossHairRenderer->SetSprite("YoshiAndMario.png", 135);
	CrossHairRenderer->SetAutoScaleRatio(3.0f);
	CrossHairRenderer->CreateAnimation("Blink", "YoshiAndMario.png", 135, 136);
	CrossHairRenderer->ChangeAnimation("Blink");
	AddActorLocation({ 0.0f, 0.0f, static_cast<float>(EOrderNum::HUD) });
}

void ACrossHair::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	Move(_DeltaTime);

	UEngineDebug::OutPutString("StartAngle : " + std::to_string(StartAngle));
}

void ACrossHair::Move(float _DeltaTime)
{
	if (StartAngle > MaxAngle) { IsPlusValue = false; }
	else if (StartAngle < MinAngle) { IsPlusValue = true; }

	(IsPlusValue) ? StartAngle += Speed * _DeltaTime : StartAngle -= Speed * _DeltaTime;

	if (UEngineInput::IsPress(VK_UP) && IsPlusValue && StartAngle > MaxAngle) { StartAngle = MaxAngle; }
	else if (UEngineInput::IsPress(VK_UP) && !IsPlusValue && StartAngle < MinAngle) { StartAngle = MinAngle; }

	FVector ParentLocation = GetWorld()->GetMainPawn()->GetActorLocation();

	FVector Offset = FVector::AngleToVectorDeg(StartAngle) * Radius;
	FVector FinalPosition = ParentLocation + Offset;

	SetActorLocation(FinalPosition);
	AddActorLocation({ 0.0f, 0.0f, static_cast<float>(EOrderNum::HUD) });
}