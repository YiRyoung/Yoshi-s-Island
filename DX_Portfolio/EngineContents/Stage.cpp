#include "PreCompile.h"
#include "Stage.h"

AStage::AStage()
{
}

AStage::~AStage()
{
}

void AStage::BeginPlay()
{
	AActor::BeginPlay();
}

void AStage::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

