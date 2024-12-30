#include "PreCompile.h"
#include "Stage101GameMode.h"
#include "Stage.h"
#include "Yoshi.h"

#include <EngineBase/EngineDebug.h>

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/Level.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>

AStage101GameMode::AStage101GameMode()
{
	Stage = GetWorld()->SpawnActor<AStage>();
	Stage->SetBackground(0, FVector({ 4608.0f, 2232.0f, 1.0f }), FVector({ 0.0f, 2232 * -0.3f, 0.0f }));

	Yoshi = GetWorld()->SpawnActor<AYoshi>();

	Camera = GetWorld()->GetMainCamera();
}

AStage101GameMode::~AStage101GameMode()
{
}

void AStage101GameMode::BeginPlay()
{
	AActor::BeginPlay();
}

void AStage101GameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	Camera->SetActorLocation( Yoshi->GetYoshiRenderer()->GetRelativeLocation());
}

void AStage101GameMode::LevelChangeStart()
{
	AActor::LevelChangeStart();
}

void AStage101GameMode::LevelChangeEnd()
{
	AActor::LevelChangeEnd();
}
