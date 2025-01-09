#include "PreCompile.h"
#include "TitleGameMode.h"
#include "Title.h"

#include <EngineBase/EngineDebug.h>

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/Level.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/EngineCamera.h>

ATitleGameMode::ATitleGameMode()
{
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image/Title");

		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
	}

	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -560.0f, 1.0f });
	Camera->GetCameraComponent()->SetZSort(0, true);

	Title = GetWorld()->SpawnActor<ATitle>();
}

ATitleGameMode::~ATitleGameMode()
{
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (true == UEngineInput::IsPress(VK_SPACE))
	{
		int Index = Title->GetBackgroundRenderer()->GetCurIndex();
		Title->SetEndAnimIndex(Index);
		Title->EndAnimation();
	}

	if (Title->IsEnd() && 0 == Title->GetBackgroundRenderer()->GetCurIndex())
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

	UEngineCore::OpenLevel("Stage101");
}

