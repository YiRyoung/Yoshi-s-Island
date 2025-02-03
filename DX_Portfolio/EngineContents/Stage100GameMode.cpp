#include "PreCompile.h"
#include "Stage100GameMode.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>

#include "YoshiGameInstance.h"
#include "ContentsEnum.h"
#include "DebugGUI.h"
#include "Stage100.h"

#include "Yoshi.h"

#include "ShyGuy.h"

#include "ScaleBlock.h"
#include "RotatePlatform.h"
#include "Platforms.h"
#include "JumpBall.h"

AStage100GameMode::AStage100GameMode()
{
	GetWorld()->CreateCollisionProfile("HeadCollision");
	GetWorld()->CreateCollisionProfile("BodyCollision");
	GetWorld()->CreateCollisionProfile("FootCollision");

	GetWorld()->CreateCollisionProfile("StickBodyCollision");
	GetWorld()->CreateCollisionProfile("StickCollision");

	GetWorld()->CreateCollisionProfile("MonsterHeadCollision");
	GetWorld()->CreateCollisionProfile("MonsterBodyCollision");

	GetWorld()->CreateCollisionProfile("PlatformCollision");
	GetWorld()->CreateCollisionProfile("JumpBallCollision");
	GetWorld()->CreateCollisionProfile("ScaleBlockDownCollision");
	
	GetWorld()->LinkCollisionProfile("MonsterHeadCollision", "FootCollision");
	GetWorld()->LinkCollisionProfile("MonsterBodyCollision", "BodyCollision");
	GetWorld()->LinkCollisionProfile("MonsterBodyCollision", "StickCollision");

	GetWorld()->LinkCollisionProfile("PlatformCollision", "FootCollision");
	GetWorld()->LinkCollisionProfile("ScaleBlockDownCollision", "HeadCollision");
	GetWorld()->LinkCollisionProfile("BodyCollision", "JumpBallCollision");


	Stage = GetWorld()->SpawnActor<AStage100>();
	Stage->SetActorLocation({ 4608 * 0.5f, 3072 * -0.5f });

	ShyGuy = GetWorld()->SpawnActor<AShyGuy>();
	ShyGuy->SetType(EShyGuyTypes::MAGETNTA);
	ShyGuy->SetActorLocation({ 1000.0f, -2600.0f, static_cast<int>(EOrderNum::PLAYER) });

	JumpBall = GetWorld()->SpawnActor<AJumpBall>();
	JumpBall->SetActorLocation({ 3305.0f, -2115.0f, static_cast<int>(EOrderNum::OBJECT) });

	/*RotatePlatform = GetWorld()->SpawnActor<ARotatePlatform>();
	RotatePlatform->SetActorLocation({ 800.0f, -2400.0f, -2.0f });*/

	ScaleBlock = GetWorld()->SpawnActor<AScaleBlock>();
	ScaleBlock->SetActorLocation({1560.0f, -2472.7f, static_cast<int>(EOrderNum::OBJECT)});
}

AStage100GameMode::~AStage100GameMode()
{
}

void AStage100GameMode::BeginPlay()
{
	AGameMode::BeginPlay();

	Stage->SwitchColImage();
	GetWorld()->GetMainPawn()->SetActorLocation({ 400.0f, -2686.0f, static_cast<float>(EOrderNum::PLAYER)});
	GetWorld()->GetMainPawn<AYoshi>()->SetEggCount(GetGameInstance<AYoshiGameInstance>()->EggCount);
}

void AStage100GameMode::Tick(float _DeltaTime)
{
	AGameMode::Tick(_DeltaTime);

	GetWorld()->GetMainPawn<AYoshi>()->CameraBoundary(Stage->GetStageScale());

	ScaleBlock->ScaleUp(ScaleBlock->GetActorLocation(), _DeltaTime);

	if (UEngineInput::IsDown('O'))
	{
		Stage->SwitchColImage();
	}
}

void AStage100GameMode::LevelChangeStart()
{
	AGameMode::LevelChangeStart();
	
	SetGUI();
}

void AStage100GameMode::LevelChangeEnd()
{
	AGameMode::LevelChangeEnd();
}

void AStage100GameMode::SetGUI()
{
#ifdef _DEBUG
	std::shared_ptr<UDebugGUI> Window = UEngineGUI::FindGUIWindow<UDebugGUI>("DebugGUI");

	if (nullptr == Window)
	{
		Window = UEngineGUI::CreateGUIWindow<UDebugGUI>("DebugGUI");
	}

	Window->SetActive(true);
#else

#endif
}
