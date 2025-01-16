#include "PreCompile.h"
#include "Stage100GameMode.h"

#include "Stage.h"

AStage100GameMode::AStage100GameMode()
{
	
}

AStage100GameMode::~AStage100GameMode()
{
}

void AStage100GameMode::BeginPlay()
{
	AActor::BeginPlay();
	
	Stage = GetWorld()->SpawnActor<AStage>();
}

void AStage100GameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

