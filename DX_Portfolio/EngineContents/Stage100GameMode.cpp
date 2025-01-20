#include "PreCompile.h"
#include "Stage100GameMode.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/CameraActor.h>

#include "Stage100.h"

AStage100GameMode::AStage100GameMode()
{
	GetWorld()->CreateCollisionProfile("HeadCollision");
	GetWorld()->CreateCollisionProfile("BodyCollision");
	GetWorld()->CreateCollisionProfile("FootCollision");

	GetWorld()->CreateCollisionProfile("DebugCollision");
}

AStage100GameMode::~AStage100GameMode()
{
}

void AStage100GameMode::BeginPlay()
{
	AActor::BeginPlay();
	
	Stage = GetWorld()->SpawnActor<AStage100>();
	Stage->SetActorLocation({ 4608 * 0.5f, 3072 * -0.5f });

	GetWorld()->GetMainPawn()->SetActorLocation({ 420.0f, -2687.0f, 0.0f });
	Stage->SwitchColStage();

}

void AStage100GameMode::Tick(float _DeltaTime)
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

