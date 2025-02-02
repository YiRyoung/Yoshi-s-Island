#include "PreCompile.h"
#include "Stage100.h"

#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCamera.h>

#include "ContentsEnum.h"
#include "Yoshi.h"

AStage100::AStage100()
{
	Stage100Res();
	Stage100Init();
}

AStage100::~AStage100()
{
}

FVector AStage100::GetStageScale() const
{
	return ColStageRenderer->GetSprite()->GetSpriteScaleToReal(0);
}

void AStage100::SwitchColImage()
{
	ColStageRenderer->SetActive(!ColStageRenderer->IsActive());
}

void AStage100::BeginPlay()
{
	AActor::BeginPlay();

	Stage100ColRes();
}

void AStage100::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
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
}

void AStage100::Stage100ColRes()
{
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
		GetWorld()->GetMainPawn<AYoshi>()->SetColImage(&ColImage);
	}
}

void AStage100::Stage100Init()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	BackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BackgroundRenderer->SetSprite("Stage100", 1);
	BackgroundRenderer->SetAutoScaleRatio(3.0f);
	FVector BackgroundScale = BackgroundRenderer->GetSprite()->GetSpriteScaleToReal(1) * BackgroundRenderer->GetAutoScaleRatio();
	BackgroundRenderer->SetRelativeLocation({ 0.0f, (BackgroundScale.Y * -0.5f), static_cast<int>(EOrderNum::BACKGROUND) });
	BackgroundRenderer->SetupAttachment(RootComponent);

	ForeBackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ForeBackgroundRenderer->SetSprite("Stage100", 2);
	ForeBackgroundRenderer->SetAutoScaleRatio(3.0f);
	ForeBackgroundRenderer->SetRelativeLocation({ 0.0f, (BackgroundScale.Y * -0.5f), static_cast<int>(EOrderNum::FOREBACKGROUND) });
	ForeBackgroundRenderer->SetupAttachment(RootComponent);

	StageRenderer = CreateDefaultSubObject<USpriteRenderer>();
	StageRenderer->SetSprite("Stage100", 3);
	StageRenderer->SetAutoScaleRatio(3.0f);
	StageRenderer->SetRelativeLocation({ 0.0f, (BackgroundScale.Y * -0.5f), static_cast<int>(EOrderNum::STAGE) });
	StageRenderer->SetupAttachment(RootComponent);

	FrontBackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
	FrontBackgroundRenderer->SetSprite("Stage100(Layer3)", 0);
	FrontBackgroundRenderer->SetAutoScaleRatio(3.0f);
	FrontBackgroundRenderer->SetRelativeLocation({ 3840.0f, -1500.0f, static_cast<int>(EOrderNum::FRONTBACKGROUND) });
	FrontBackgroundRenderer->CreateAnimation("Start", "Stage100(Layer3)", { 0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1, 1 }, 0.2f);
	FrontBackgroundRenderer->ChangeAnimation("Start");
	FrontBackgroundRenderer->SetupAttachment(RootComponent);

	ColStageRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ColStageRenderer->SetSprite("Stage100", 0);
	ColStageRenderer->SetRelativeLocation({ 0.0f, (BackgroundScale.Y * -0.5f), 0.0f });
	ColStageRenderer->SetupAttachment(RootComponent);
}

