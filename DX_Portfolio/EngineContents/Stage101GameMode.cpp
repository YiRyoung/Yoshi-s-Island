#include "PreCompile.h"
#include "Stage101GameMode.h"
#include "Stage.h"
#include "Yoshi.h"

#include <EngineBase/EngineDebug.h>

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/Level.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/EngineCamera.h>

AStage101GameMode::AStage101GameMode()
{
	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -560.0f, 1.0f });
	Camera->GetCameraComponent()->SetZSort(0, true);

	Stage = GetWorld()->SpawnActor<AStage>();
	Stage->SetBackground("Stage100(Layer0).png", FVector{0.0f, 0.0f, 5.0f});
	Yoshi = GetWorld()->SpawnActor<AYoshi>();
}

AStage101GameMode::~AStage101GameMode()
{
}

void AStage101GameMode::BeginPlay()
{
	AActor::BeginPlay();
}

void AStage101GameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	Camera->SetActorLocation({ Yoshi->GetYoshiRenderer()->GetTransformRef().RelativeLocation.X, Yoshi->GetYoshiRenderer()->GetTransformRef().RelativeLocation.Y, -560.0f});
	
	SetCameraBoundary();
}

void AStage101GameMode::LevelChangeStart()
{
	AActor::LevelChangeStart();
}

void AStage101GameMode::LevelChangeEnd()
{
	AActor::LevelChangeEnd();
}

void AStage101GameMode::SetCameraBoundary()
{
	FVector Size = UEngineCore::GetScreenScale();
	//FVector BackgroundSize = Stage->GetBackgroundScale();

	FVector CameraPos = Camera->GetActorTransform().RelativeLocation;
}
