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

	Yoshi = GetWorld()->SpawnActor<AYoshi>();
	Yoshi->SetActorLocation({ 100, -1000 });
}

AStage100GameMode::~AStage100GameMode()
{
}

void AStage100GameMode::BeginPlay()
{
	AActor::BeginPlay();
}

void AStage100GameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	Camera->SetActorLocation({ Yoshi->GetActorLocation().X, Yoshi->GetActorLocation().Y, -520.0f});
	// Yoshi에서 검사할 위치를 가져와서 Stage에서 충돌 색상을 확인하고 확인한 색을 다시 Yoshi에게 전달
	Yoshi->SetColor(Stage->GetPixelColor(Yoshi->GetCheckPos()));
}

void AStage100GameMode::LevelChangeStart()
{
	AActor::LevelChangeStart();
}

void AStage100GameMode::LevelChangeEnd()
{
	AActor::LevelChangeEnd();
}