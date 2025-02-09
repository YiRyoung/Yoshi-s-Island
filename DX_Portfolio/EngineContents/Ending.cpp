#include "PreCompile.h"
#include "Ending.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCamera.h>
#include <EngineCore/SpriteRenderer.h>

#include "ContentsEnum.h"

AEnding::AEnding()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -560.0f, 1.0f });
	Camera->GetCameraComponent()->SetZSort(0, true);
	
	BlackScreen = CreateDefaultSubObject<USpriteRenderer>();
	BlackScreen->SetupAttachment(RootComponent);
	BlackScreen->SetTexture("BlackScreen.png");
	BlackScreen->SetScale3D({ 768, 660, 1 });
	BlackScreen->AddWorldLocation({ 0.0f, 0.0f, static_cast<float>(EOrderNum::BACKGROUND) });

	Yoshi = CreateDefaultSubObject<USpriteRenderer>();
	Yoshi->SetupAttachment(RootComponent);
	Yoshi->SetSprite("YoshiAndMario.png", 186);
	Yoshi->SetAutoScaleRatio(3.0f);
	Yoshi->SetWorldLocation({ 0.0f, -200.0f, static_cast<float>(EOrderNum::PLAYER) });
	Yoshi->CreateAnimation("Ending", "YoshiAndMario.png", 186, 190, 0.2f);
	Yoshi->ChangeAnimation("Ending");

	for (int i = 0; i < 5; i++)
	{
		std::shared_ptr<USpriteRenderer> Render = CreateDefaultSubObject<USpriteRenderer>();
		Render->SetupAttachment(RootComponent);
		Render->SetSprite("Goal.png", i);
		Render->SetAutoScaleRatio(2.0f);
		Render->SetWorldLocation({ (-180.0f + (i * 80.0f)), 60.0f, static_cast<float>(EOrderNum::OBJECT) });
		Renders.push_back(Render);
	}
}

AEnding::~AEnding()
{
}

void AEnding::BeginPlay()
{
	AActor::BeginPlay();
}

void AEnding::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	SetIsMoveUp();
	FontMoving(_DeltaTime);

	
}

void AEnding::SetIsMoveUp()
{
	if (IsMoveUp && Renders[0]->GetWorldLocation().Y >= 100.0f)
	{
		IsMoveUp = false;
	}
	else if (!IsMoveUp && Renders[0]->GetWorldLocation().Y <= 20.0f)
	{
		IsMoveUp = true;
	}

}

void AEnding::FontMoving(float _DeltaTime)
{
	if (IsMoveUp)
	{
		Renders[0]->AddWorldLocation(FVector::UP * Speed * _DeltaTime);
		Renders[1]->AddWorldLocation(FVector::DOWN * Speed * _DeltaTime);
		Renders[2]->AddWorldLocation(FVector::UP * Speed * _DeltaTime);
		Renders[3]->AddWorldLocation(FVector::DOWN * Speed * _DeltaTime);
		Renders[4]->AddWorldLocation(FVector::UP * Speed * _DeltaTime);
	}
	else
	{
		Renders[0]->AddWorldLocation(FVector::DOWN * Speed * _DeltaTime);
		Renders[1]->AddWorldLocation(FVector::UP * Speed * _DeltaTime);
		Renders[2]->AddWorldLocation(FVector::DOWN * Speed * _DeltaTime);
		Renders[3]->AddWorldLocation(FVector::UP * Speed * _DeltaTime);
		Renders[4]->AddWorldLocation(FVector::DOWN * Speed * _DeltaTime);
	}
}

