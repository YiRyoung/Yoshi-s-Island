#include "PreCompile.h"
#include "Stage100.h"

#include <EngineBase/EngineDebug.h>

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/DefaultSceneComponent.h>

AStage100::AStage100()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;
}

AStage100::~AStage100()
{
}

void AStage100::SetBackground()
{
	BackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BackgroundRenderer->SetSprite("Stage100", 0);
	BackgroundRenderer->SetAutoScaleRatio(3.0f);
	FVector BackgroundScale = (BackgroundRenderer->GetSprite()->GetTexture()->GetTextureSize()) * BackgroundRenderer->GetAutoScaleRatio();
	FVector ResultScale = { (BackgroundScale.X * 0.5f), (BackgroundScale.Y * -1.0f), 5.0f };
	BackgroundRenderer->SetRelativeLocation({(BackgroundScale.X * 0.5f), (BackgroundScale.Y * -1.0f), 5.0f }); /* Window 화면의 절반만큼 더해주기 */
	BackgroundRenderer->SetupAttachment(RootComponent);

	ForeBackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
	ForeBackgroundRenderer->SetSprite("Stage100", 1);
	ForeBackgroundRenderer->SetAutoScaleRatio(3.0f);
	FVector ForeBackgroundScale = (ForeBackgroundRenderer->GetSprite()->GetTexture()->GetTextureSize()) * ForeBackgroundRenderer->GetAutoScaleRatio();
	ForeBackgroundRenderer->SetRelativeLocation({ (ForeBackgroundScale.X * 0.167f), (ForeBackgroundScale.Y * -1.0f), 4.0f });
	ForeBackgroundRenderer->SetupAttachment(RootComponent);

	StageRenderer = CreateDefaultSubObject<USpriteRenderer>();
	StageRenderer->SetSprite("Stage100", 2);
	StageRenderer->SetAutoScaleRatio(3.0f);
	FVector StageScale = (StageRenderer->GetSprite()->GetTexture()->GetTextureSize()) * StageRenderer->GetAutoScaleRatio();
	StageRenderer->SetRelativeLocation({(StageScale.X * 0.5f), (StageScale.Y * -1.0f), 3.0f});
	StageRenderer->SetupAttachment(RootComponent);

	FrontBackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
	FrontBackgroundRenderer->SetSprite("Stage100(Layer3)", 0);
	FrontBackgroundRenderer->SetAutoScaleRatio(3.0f);
	FVector FrontBackgroundScale = (FrontBackgroundRenderer->GetSprite()->GetTexture()->GetTextureSize()) * FrontBackgroundRenderer->GetAutoScaleRatio();
	FrontBackgroundRenderer->SetRelativeLocation({ (FrontBackgroundScale.X * 0.5f), -3015.0f, -1.0f });
	FrontBackgroundRenderer->CreateAnimation("Start", "Stage100(Layer3)", { 0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1, 1 }, 0.3f);
	FrontBackgroundRenderer->ChangeAnimation("Start");
	FrontBackgroundRenderer->SetupAttachment(RootComponent);
}

void AStage100::BeginPlay()
{
	AActor::BeginPlay();
}

void AStage100::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

