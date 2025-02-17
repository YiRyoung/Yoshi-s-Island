#include "PreCompile.h"
#include "TitleGameMode.h"

#include <EngineCore/TimeEventComponent.h>

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/SpriteRenderer.h>

#include "Title.h"
#include "YoshiGameInstance.h"
#include "ContentsEnum.h"
#include "KeyNoticeGUI.h"

ATitleGameMode::ATitleGameMode()
{
	Title = GetWorld()->SpawnActor<ATitle>();
	TimeEvent = CreateDefaultSubObject<UTimeEventComponent>();
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

	if (UEngineInput::IsDown(VK_SPACE))
	{
		SoundPlayer = UEngineSound::Play("Coin.wav");
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

	SoundPlayer = UEngineSound::Play("Yoshi's Island.mp3");
	SoundPlayer.Loop(-1);

#ifdef _DEBUG

#else
	std::shared_ptr<UKeyNoticeGUI> KeyWindow = UEngineGUI::FindGUIWindow<UKeyNoticeGUI>("KeyNoticeGUI");

	if (nullptr == KeyWindow)
	{
		KeyWindow = UEngineGUI::CreateGUIWindow<UKeyNoticeGUI>("KeyNoticeGUI");
	}

	KeyWindow->SetActive(true);
#endif
}

void ATitleGameMode::LevelChangeEnd()
{
	AActor::LevelChangeEnd();

	UEngineSound::AllSoundStop();
	UEngineCore::OpenLevel("Stage100");
}