#include "PreCompile.h"
#include "Stage102GameMode.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/CameraActor.h>

#include "Stage102.h"

AStage102GameMode::AStage102GameMode()
{
	GetWorld()->CreateCollisionProfile("HeadCollision");
	GetWorld()->CreateCollisionProfile("BodyCollision");
	GetWorld()->CreateCollisionProfile("FootCollision");

	GetWorld()->CreateCollisionProfile("DebugCollision");
}

AStage102GameMode::~AStage102GameMode()
{
}

void AStage102GameMode::BeginPlay()
{
	AActor::BeginPlay();
	Stage = GetWorld()->SpawnActor<AStage102>();
	Stage->SetActorLocation({ 3072 * 0.5f, 777 * -0.5f });

	GetWorld()->GetMainPawn()->SetActorLocation({ 100.0f, -300.0f, 0.0f });
	Stage->SwitchColStage();
}

void AStage102GameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (UEngineInput::IsDown('V'))
	{
		Stage->SwitchColStage();
	}

	if (UEngineInput::IsDown('F'))
	{
		GetWorld()->GetMainCamera()->FreeCameraSwitch();
	}
}

