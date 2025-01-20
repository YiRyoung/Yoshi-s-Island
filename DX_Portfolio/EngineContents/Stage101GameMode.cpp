#include "PreCompile.h"
#include "Stage101GameMode.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/CameraActor.h>

#include "Stage101.h"

AStage101GameMode::AStage101GameMode()
{
	GetWorld()->CreateCollisionProfile("HeadCollision");
	GetWorld()->CreateCollisionProfile("BodyCollision");
	GetWorld()->CreateCollisionProfile("FootCollision");

	GetWorld()->CreateCollisionProfile("DebugCollision");
}

AStage101GameMode::~AStage101GameMode()
{
}

void AStage101GameMode::BeginPlay()
{
	AActor::BeginPlay();

	Stage = GetWorld()->SpawnActor<AStage101>();
	Stage->SetActorLocation({ 12288 * 0.5f, 2241 * -0.5f });

	GetWorld()->GetMainPawn()->SetActorLocation({ 100.0f, -1850.0f, 0.0f });
	Stage->SwitchColStage();
}

void AStage101GameMode::Tick(float _DeltaTime)
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

