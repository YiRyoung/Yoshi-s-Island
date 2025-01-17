#include "PreCompile.h"
#include "Stage100.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCamera.h>

#include "ContentsEnum.h"
#include "Yoshi.h"

AStage100::AStage100()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Stage100Res();
	Stage100Init();
}

AStage100::~AStage100()
{
}

void AStage100::SwitchColStage()
{
	ColStageRenderer->SetActive(!ColStageRenderer->IsActive());
}

void AStage100::BeginPlay()
{
	AActor::BeginPlay();
	SwitchColStage();
}

void AStage100::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	CameraBoundary();
}

void AStage100::Stage100Res()
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

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image/Stage100");
		UEngineFile ImageFiles = Dir.GetFile("ColStage100.png");

		ColImage.Load(nullptr, ImageFiles.GetPathToString());
	}

	AYoshi* Player = dynamic_cast<AYoshi*>(GetWorld()->GetMainPawn());
	Player->SetColImage(&ColImage);
	Player->SetCamera(GetWorld()->GetMainCamera());
}

void AStage100::Stage100Init()
{
	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -560.0f, 1.0f });
	Camera->GetCameraComponent()->SetZSort(0, true);

	BackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BackgroundRenderer->SetSprite("Stage100", 1);
	BackgroundRenderer->SetAutoScaleRatio(3.0f);
	FVector BackgroundScale = BackgroundRenderer->GetSprite()->GetSpriteScaleToReal(1) * BackgroundRenderer->GetAutoScaleRatio();
	BackgroundRenderer->SetRelativeLocation({ 0.0f, (BackgroundScale.Y * -0.5f), static_cast<int>(EOrderNum::BACKGROUND)});
	BackgroundRenderer->SetupAttachment(RootComponent);

	ForeBackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ForeBackgroundRenderer->SetSprite("Stage100", 2);
	ForeBackgroundRenderer->SetAutoScaleRatio(3.0f);
	ForeBackgroundRenderer->SetRelativeLocation({ 0.0f, (BackgroundScale.Y * -0.5f), static_cast<int>(EOrderNum::FOREBACKGROUND)});
	ForeBackgroundRenderer->SetupAttachment(RootComponent);

	StageRenderer = CreateDefaultSubObject<USpriteRenderer>();
	StageRenderer->SetSprite("Stage100", 3);
	StageRenderer->SetAutoScaleRatio(3.0f);
	StageRenderer->SetRelativeLocation({ 0.0f, (BackgroundScale.Y * -0.5f), static_cast<int>(EOrderNum::STAGE)});
	StageRenderer->SetupAttachment(RootComponent);

	FrontBackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
	FrontBackgroundRenderer->SetSprite("Stage100(Layer3)", 0);
	FrontBackgroundRenderer->SetAutoScaleRatio(3.0f);
	FrontBackgroundRenderer->SetRelativeLocation({ 3840.0f, -1500.0f, static_cast<int>(EOrderNum::FRONTBACKGROUND)});
	FrontBackgroundRenderer->CreateAnimation("Start", "Stage100(Layer3)", { 0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1, 1 }, 0.2f);
	FrontBackgroundRenderer->ChangeAnimation("Start");
	FrontBackgroundRenderer->SetupAttachment(RootComponent);

	ColStageRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ColStageRenderer->SetSprite("Stage100", 0);
	ColStageRenderer->SetRelativeLocation({ 0.0f, (BackgroundScale.Y * -0.5f), 0.0f });
	ColStageRenderer->SetupAttachment(RootComponent);
}

void AStage100::CameraBoundary()
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
