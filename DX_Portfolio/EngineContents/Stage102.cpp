#include "PreCompile.h"
#include "Stage102.h"

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCamera.h>

#include "ContentsEnum.h"
#include "Yoshi.h"

AStage102::AStage102()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Stage102Res();
	Stage102Init();
}

AStage102::~AStage102()
{
}

void AStage102::SwitchColStage()
{
	ColStageRenderer->SetActive(!ColStageRenderer->IsActive());
}

void AStage102::BeginPlay()
{
	AActor::BeginPlay();
	SwitchColStage();
}

void AStage102::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	CameraBoundary();
}

void AStage102::Stage102Res()
{
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image/Stage102");

		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
	}

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image/Stage102/Stage102(Layer1)");

		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
	}

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image/Stage102");
		UEngineFile ImageFiles = Dir.GetFile("ColStage102.png");

		ColImage.Load(nullptr, ImageFiles.GetPathToString());
	}

	AYoshi* Player = dynamic_cast<AYoshi*>(GetWorld()->GetMainPawn());
	Player->SetColImage(&ColImage);
	Player->SetCamera(GetWorld()->GetMainCamera());
}

void AStage102::Stage102Init()
{
	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -560.0f, 1.0f });
	Camera->GetCameraComponent()->SetZSort(0, true);

	BackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BackgroundRenderer->SetSprite("Stage102", 1);
	BackgroundRenderer->SetAutoScaleRatio(3.0f);
	FVector BackgroundScale = BackgroundRenderer->GetSprite()->GetSpriteScaleToReal(1) * BackgroundRenderer->GetAutoScaleRatio();
	BackgroundRenderer->SetRelativeLocation({ 0.0f, (BackgroundScale.Y * -0.496f), static_cast<int>(EOrderNum::BACKGROUND) });
	BackgroundRenderer->SetupAttachment(RootComponent);

	ForeBackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ForeBackgroundRenderer->SetSprite("Stage102(Layer1)", 0);
	ForeBackgroundRenderer->SetAutoScaleRatio(3.0f);
	ForeBackgroundRenderer->SetRelativeLocation({ 0.0f, (BackgroundScale.Y * -0.496f), static_cast<int>(EOrderNum::FOREBACKGROUND) });
	ForeBackgroundRenderer->CreateAnimation("Start", "Stage102(Layer1)", 0, 7, 0.5f);
	ForeBackgroundRenderer->ChangeAnimation("Start");
	ForeBackgroundRenderer->SetupAttachment(RootComponent);

	StageRenderer = CreateDefaultSubObject<USpriteRenderer>();
	StageRenderer->SetSprite("Stage102", 2);
	StageRenderer->SetAutoScaleRatio(3.0f);
	StageRenderer->SetRelativeLocation({ 0.0f, (BackgroundScale.Y * -0.5f), static_cast<int>(EOrderNum::STAGE) });
	StageRenderer->SetupAttachment(RootComponent);

	FrontBackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
	FrontBackgroundRenderer->SetSprite("Stage102", 3);
	FrontBackgroundRenderer->SetAutoScaleRatio(3.0f);
	FrontBackgroundRenderer->SetRelativeLocation({ 0.0f, (BackgroundScale.Y * -0.5f), static_cast<int>(EOrderNum::FRONTBACKGROUND) });
	FrontBackgroundRenderer->SetupAttachment(RootComponent);

	ColStageRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ColStageRenderer->SetSprite("Stage102", 0);
	ColStageRenderer->SetRelativeLocation({ 0.0f, (BackgroundScale.Y * -0.5f), 0.0f });
	ColStageRenderer->SetupAttachment(RootComponent);
}

void AStage102::CameraBoundary()
{
	AYoshi* Player = GetWorld()->GetMainPawn<AYoshi>();
	FVector CameraPivot = Player->GetCameraPivot();

	Camera->SetActorLocation({ GetWorld()->GetMainPawn()->GetActorLocation().X, GetWorld()->GetMainPawn()->GetActorLocation().Y, -520.0f });

	FVector ResultCameraPos = { 0.0f, 0.0f, 0.0f };
	FVector ScreenSize = UEngineCore::GetScreenScale();
	FVector MapSize = ColStageRenderer->GetWorldScale3D();
	FVector CameraPos = Camera->GetActorLocation() + CameraPivot;

	// SetBoundary
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
		ResultCameraPos.X = GetWorld()->GetMainPawn()->GetActorLocation().X + CameraPivot.X;
	}

	if ((ScreenSize.Y * -0.5f) <= CameraPos.Y + 15.0f)
	{
		ResultCameraPos.Y = (ScreenSize.Y * -0.5f);
	}
	else if ((-MapSize.Y + (ScreenSize.Y * 0.5f)) >= CameraPos.Y)
	{
		ResultCameraPos.Y = (-MapSize.Y + (ScreenSize.Y * 0.5f));
	}
	else
	{
		ResultCameraPos.Y = GetWorld()->GetMainPawn()->GetActorLocation().Y + CameraPivot.Y;
	}

	Camera->SetActorLocation({ ResultCameraPos.X, ResultCameraPos.Y + 15.0f, -520.0f });

}
