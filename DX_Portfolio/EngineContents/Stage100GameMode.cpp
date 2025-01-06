#include "PreCompile.h"
#include "Stage100GameMode.h"
#include "Stage100.h"
#include "Yoshi.h"

#include <EngineBase/EngineDebug.h>

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/Level.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/EngineCamera.h>

AStage100GameMode::AStage100GameMode()
{
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image/Stage100");

		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
	}

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image/Stage100/Stage100(Layer3)");

		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
	}

	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -560.0f, 1.0f });
	Camera->GetCameraComponent()->SetZSort(0, true);

	Stage = GetWorld()->SpawnActor<AStage100>();
	Stage->SetBackground();

	Yoshi = GetWorld()->SpawnActor<AYoshi>();
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

	Camera->SetActorLocation({ Yoshi->GetYoshiRenderer()->GetTransformRef().RelativeLocation.X, Yoshi->GetYoshiRenderer()->GetTransformRef().RelativeLocation.Y, -520.0f});
	
	SetCameraBoundary();
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
	FVector Size = UEngineCore::GetScreenScale();
	//FVector BackgroundSize = Stage->GetBackgroundScale();

	FVector CameraPos = Camera->GetActorTransform().RelativeLocation;
}
