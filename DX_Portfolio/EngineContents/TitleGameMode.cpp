#include "PreCompile.h"
#include "TitleGameMode.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/SpriteRenderer.h>

#include "Title.h"

ATitleGameMode::ATitleGameMode()
{
	Title = GetWorld()->SpawnActor<ATitle>();
}

ATitleGameMode::~ATitleGameMode()
{
}

void ATitleGameMode::BeginPlay()
{
	AActor::BeginPlay();
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (UEngineInput::IsPress(VK_SPACE))
	{
		int Index = Title->GetRenderer()->GetCurIndex();
		Title->EndAnimation(Index);
	}

	if (Title->IsEnd() && Title->GetRenderer()->GetCurIndex() == 0)
	{
		LevelChangeEnd();
	}
}

void ATitleGameMode::LevelChangeStart()
{
	AActor::LevelChangeStart();
}

void ATitleGameMode::LevelChangeEnd()
{
	AActor::LevelChangeEnd();

	UEngineCore::OpenLevel("Stage100");
}

