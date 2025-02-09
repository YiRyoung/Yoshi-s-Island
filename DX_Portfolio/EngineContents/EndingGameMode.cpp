#include "PreCompile.h"
#include "EndingGameMode.h"

#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include "Ending.h"

AEndingGameMode::AEndingGameMode()
{
	Ending = GetWorld()->SpawnActor<AEnding>();
}

AEndingGameMode::~AEndingGameMode()
{
}

void AEndingGameMode::LevelChangeStart()
{
	AGameMode::LevelChangeStart();
	UEngineGUI::AllWindowOff();

	SoundPlayer = UEngineSound::Play("Goal.mp3");
	SoundPlayer.Loop(-1);
}

