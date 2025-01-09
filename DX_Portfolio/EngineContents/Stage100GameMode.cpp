#include "PreCompile.h"
#include "Stage100GameMode.h"
#include "Stage100.h"
#include "Yoshi.h"

#include <EngineBase/EngineDebug.h>

#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineWinImage.h>

#include <EngineCore/Level.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/EngineCamera.h>

AStage100GameMode::AStage100GameMode()
{
	
	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -560.0f, 1.0f });
	Camera->GetCameraComponent()->SetZSort(0, true);

	Stage = GetWorld()->SpawnActor<AStage100>();
	Stage->SetBackground();
	Stage->SetActorLocation({ 4608 * 0.5f, 3072 * -0.5f });
}

AStage100GameMode::~AStage100GameMode()
{
}

void AStage100GameMode::BeginPlay()
{
	AActor::BeginPlay();
	GetWorld()->GetMainPawn()->SetActorLocation({ 200.0f, -2690.0f, 0.0f });
	Stage->SwitchColStage(false);
}

void AStage100GameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	
	dynamic_cast<AYoshi*>(GetWorld()->GetMainPawn())->SetColor(Stage->GetPixelColor(dynamic_cast<AYoshi*>(GetWorld()->GetMainPawn())->GetCheckPos()));

	SetCameraBoundary();

	if (true == UEngineInput::IsDown('V'))
	{
		bool IsTrue = (Stage->GetColStageOn());
		Stage->SwitchColStage(!IsTrue);
	}
}

void AStage100GameMode::LevelChangeStart()
{
	AActor::LevelChangeStart();
}

void AStage100GameMode::LevelChangeEnd()
{
	AActor::LevelChangeEnd();
}

void AStage100GameMode::SetCameraBoundary()
{
	Camera->SetActorLocation({ GetWorld()->GetMainPawn()->GetActorLocation().X, GetWorld()->GetMainPawn()->GetActorLocation().Y, -520.0f});
	
	FVector ResultCameraPos = { 0.0f, 0.0f, 0.0f };
	FVector ScreenSize = UEngineCore::GetScreenScale();
	FVector MapSize = Stage->GetMapScale();
	FVector CameraPos = Camera->GetActorLocation();

	if ((ScreenSize.X * 0.5f) >= CameraPos.X)
	{
		ResultCameraPos.X = ScreenSize.X * 0.5f;
	}
	else if (MapSize.X - (ScreenSize.X * 0.5f) <= CameraPos.X)
	{
		ResultCameraPos.X = MapSize.X - (ScreenSize.X * 0.5f);
	}
	else
	{
		ResultCameraPos.X = GetWorld()->GetMainPawn()->GetActorLocation().X;
	}

	if ((ScreenSize.Y * -0.5f) <= CameraPos.Y)
	{
		ResultCameraPos.Y = (ScreenSize.Y * -0.5f);
	}
	else if ((-MapSize.Y + (ScreenSize.Y * 0.5f)) >= CameraPos.Y)
	{
		ResultCameraPos.Y = (-MapSize.Y + (ScreenSize.Y * 0.5f));
	}
	else
	{
		ResultCameraPos.Y = GetWorld()->GetMainPawn()->GetActorLocation().Y;
	}

	Camera->SetActorLocation({ ResultCameraPos.X, ResultCameraPos.Y, -520.0f });
}