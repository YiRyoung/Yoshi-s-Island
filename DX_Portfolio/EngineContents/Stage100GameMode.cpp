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
}

void AStage100GameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	Camera->SetActorLocation({ GetWorld()->GetMainPawn()->GetActorLocation().X, GetWorld()->GetMainPawn()->GetActorLocation().Y, -520.0f});
	dynamic_cast<AYoshi*>(GetWorld()->GetMainPawn())->SetColor(Stage->GetPixelColor(dynamic_cast<AYoshi*>(GetWorld()->GetMainPawn())->GetCheckPos()));

	UEngineDebug::OutPutString("Pos : " + std::to_string(GetWorld()->GetMainPawn()->GetActorLocation().X) + ","
		+ std::to_string(GetWorld()->GetMainPawn()->GetActorLocation().Y));
}

void AStage100GameMode::LevelChangeStart()
{
	AActor::LevelChangeStart();
}

void AStage100GameMode::LevelChangeEnd()
{
	AActor::LevelChangeEnd();
}