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
	Yoshi->GetYoshiRenderer()->SetRelativeLocation({ 220.0f, -2690.0f, 0.0f });
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

	Camera->SetActorLocation({ Yoshi->GetYoshiRenderer()->GetTransformRef().RelativeLocation.X, Yoshi->GetYoshiRenderer()->GetTransformRef().RelativeLocation.Y, -520.0f });
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
	FVector ResultCameraPos = { 0.0f, 0.0f, 0.0f };
	FVector ScrrenSize = UEngineCore::GetScreenScale();
	FVector MapSize = Stage->GetMapScale();
	FVector CameraPos = Camera->GetActorTransform().RelativeLocation;

	if ((ScrrenSize.X * 0.5f) >= CameraPos.X)
	{
		ResultCameraPos.X = ScrrenSize.X * 0.5f;
	}
	else if ((MapSize.X - (ScrrenSize.X * 0.5f)) <= CameraPos.X)
	{
		ResultCameraPos.X = MapSize.X - (ScrrenSize.X * 0.5f);
	}
	else
	{
		ResultCameraPos.X = Yoshi->GetYoshiRenderer()->GetTransformRef().RelativeLocation.X;
	}

	if ((ScrrenSize.Y * -0.5f) <= CameraPos.Y)
	{
		ResultCameraPos.Y = (ScrrenSize.Y * -0.5f);
	}
	else if ((-MapSize.Y + (ScrrenSize.Y * 0.5f)) >= CameraPos.Y)
	{
		ResultCameraPos.Y = (-MapSize.Y + (ScrrenSize.Y * 0.5f));
	}
	else
	{
		ResultCameraPos.Y = Yoshi->GetYoshiRenderer()->GetTransformRef().RelativeLocation.Y;
	}
	Camera->SetActorLocation({ ResultCameraPos.X, ResultCameraPos.Y, -560.0f });
}
