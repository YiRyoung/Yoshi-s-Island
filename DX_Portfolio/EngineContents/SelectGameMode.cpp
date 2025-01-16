#include "PreCompile.h"
#include "SelectGameMode.h"

#include <EnginePlatform/EngineInput.h>

#include "Select.h"

ASelectGameMode::ASelectGameMode()
{
	Select = GetWorld()->SpawnActor<ASelect>();
}

ASelectGameMode::~ASelectGameMode()
{
}

void ASelectGameMode::BeginPlay()
{
	AActor::BeginPlay();
}

void ASelectGameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (UEngineInput::IsPress('N'))
	{
		UEngineCore::OpenLevel("State100");
	}
}

void ASelectGameMode::LevelChangeStart()
{
	AActor::LevelChangeStart();
}

void ASelectGameMode::LevelChangeEnd()
{
	AActor::LevelChangeEnd();
}
