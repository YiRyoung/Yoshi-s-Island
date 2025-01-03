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

class TestWindow : public UEngineGUIWindow
{
public:
	void OnGUI() override
	{
		ImGui::Button("WindowButton");
		ImGui::SameLine();
	}
};

ATitleGameMode::ATitleGameMode()
{
	Title = GetWorld()->SpawnActor<ATitle>();

	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });

	UEngineGUI::CreateGUIWindow<TestWindow>("TestWindow");
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

