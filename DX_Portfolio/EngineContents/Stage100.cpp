#include "PreCompile.h"
#include "Stage100.h"

#include <EngineBase/EngineDebug.h>

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/DefaultSceneComponent.h>

#include "Yoshi.h"

AStage100::AStage100()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

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
		Dir.Append("Image");
		UEngineFile ImageFiles = Dir.GetFile("ColStage100.png");

		ColImage.Load(nullptr, ImageFiles.GetPathToString());
	}

	AYoshi* Player = dynamic_cast<AYoshi*>(GetWorld()->GetMainPawn());
	Player->SetColImage(&ColImage);
}

AStage100::~AStage100()
{
}

UColor AStage100::GetPixelColor(FVector _Pos)
{
	return ColImage.GetColor(_Pos, UColor{ 255, 255, 255, 255 });
}

void AStage100::SetBackground()
{
	BackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BackgroundRenderer->SetSprite("Stage100", 0);
	BackgroundRenderer->SetAutoScaleRatio(3.0f);
	FVector BackgroundScale = (BackgroundRenderer->GetSprite()->GetTexture()->GetTextureSize()) * BackgroundRenderer->GetAutoScaleRatio();
	BackgroundRenderer->SetRelativeLocation({0.0f, (BackgroundScale.Y * -0.5f), 5.0f });
	BackgroundRenderer->SetupAttachment(RootComponent);

	ForeBackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ForeBackgroundRenderer->SetSprite("Stage100", 1);
	ForeBackgroundRenderer->SetAutoScaleRatio(3.0f);
	FVector ForeBackgroundScale = (ForeBackgroundRenderer->GetSprite()->GetTexture()->GetTextureSize()) * ForeBackgroundRenderer->GetAutoScaleRatio();
	ForeBackgroundRenderer->SetRelativeLocation({0.0f, (ForeBackgroundScale.Y * -0.5f), 4.0f });
	ForeBackgroundRenderer->SetupAttachment(RootComponent);

	StageRenderer = CreateDefaultSubObject<USpriteRenderer>();
	StageRenderer->SetSprite("Stage100", 2);
	StageRenderer->SetAutoScaleRatio(3.0f);
	FVector StageScale = (StageRenderer->GetSprite()->GetTexture()->GetTextureSize()) * StageRenderer->GetAutoScaleRatio();
	StageRenderer->SetRelativeLocation({0.0f, (StageScale.Y * -0.5f), 3.0f});
	StageRenderer->SetupAttachment(RootComponent);

	FrontBackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
	FrontBackgroundRenderer->SetSprite("Stage100(Layer3)", 0);
	FrontBackgroundRenderer->SetAutoScaleRatio(3.0f);
	FVector FrontBackgroundScale = (FrontBackgroundRenderer->GetSprite()->GetTexture()->GetTextureSize()) * FrontBackgroundRenderer->GetAutoScaleRatio();
	FrontBackgroundRenderer->SetRelativeLocation({ FrontBackgroundScale.X * 0.312f, -1500, -20.0f });
	FrontBackgroundRenderer->CreateAnimation("Start", "Stage100(Layer3)", { 0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1, 1 }, 0.2f);
	FrontBackgroundRenderer->ChangeAnimation("Start");
	FrontBackgroundRenderer->SetupAttachment(RootComponent);

	ColStageRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ColStageRenderer->SetTexture("ColStage100.png");
	ColStageRenderer->SetScale3D({ 4608, 3072, 1 });
	MapScale = ColStageRenderer->GetWorldScale3D();
	ColStageRenderer->SetupAttachment(RootComponent);
}

void AStage100::BeginPlay()
{
	AActor::BeginPlay();
}

void AStage100::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

