#include "PreCompile.h"
#include "Stage101.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCamera.h>

#include "ContentsEnum.h"
#include "Yoshi.h"

AStage101::AStage101()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Stage101Res();
	Stage101Init();
}

AStage101::~AStage101()
{
}

void AStage101::SwitchColStage()
{
	ColStageRenderer->SetActive(!ColStageRenderer->IsActive());
}

void AStage101::BeginPlay()
{
	AActor::BeginPlay();
	SwitchColStage();
}

void AStage101::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	CameraBoundary();
}

void AStage101::Stage101Res()
{
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image/Stage101");

		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
	}

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image/Stage101/Stage101(Layer1)");

		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
	}

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image/Stage101");
		UEngineFile ImageFiles = Dir.GetFile("ColStage101.png");

		ColImage.Load(nullptr, ImageFiles.GetPathToString());
	}

	AYoshi* Player = dynamic_cast<AYoshi*>(GetWorld()->GetMainPawn());
	Player->SetColImage(&ColImage);
	Player->SetCamera(GetWorld()->GetMainCamera());
}

void AStage101::Stage101Init()
{
}

void AStage101::CameraBoundary()
{
	Camera->SetActorLocation({ GetWorld()->GetMainPawn()->GetActorLocation().X, GetWorld()->GetMainPawn()->GetActorLocation().Y, -520.0f });

	FVector ResultCameraPos = { 0.0f, 0.0f, 0.0f };
	FVector ScreenSize = UEngineCore::GetScreenScale();
	FVector MapSize = ColStageRenderer->GetWorldScale3D();
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

	Camera->SetActorLocation({ ResultCameraPos.X, ResultCameraPos.Y + 160.0f, -520.0f });
}
