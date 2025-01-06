#include "PreCompile.h"
#include "Stage.h"

#include <EngineBase/EngineDebug.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/DefaultSceneComponent.h>

AStage::AStage()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;
}

AStage::~AStage()
{
}

void AStage::SetBackground(std::string_view _BackgroundName, FVector _Pos)
{
	BackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BackgroundRenderer->SetSprite("Stage", 0);
	BackgroundRenderer->SetAutoScaleRatio(3.0f);
	FVector NewVector = BackgroundRenderer->GetSprite()->GetTexture()->GetTextureSize();
	BackgroundRenderer->SetRelativeLocation({(NewVector.X * 3) * 0.5f, (NewVector.Y * 3) * -1.0f, 5.0f });
	BackgroundRenderer->SetupAttachment(RootComponent);

	//ForeBackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//ForeBackgroundRenderer->SetSprite("Stage", 1);
	//ForeBackgroundRenderer->SetAutoScaleRatio(3.0f);
	//ForeBackgroundRenderer->SetRelativeLocation(FVector({ 0.0f, 0.0f, 4.0f, 1.0f }));
	//ForeBackgroundRenderer->SetupAttachment(RootComponent);

	//StageRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//StageRenderer->SetSprite("Stage", 2);
	//StageRenderer->SetAutoScaleRatio(3.0f);
	//StageRenderer->SetRelativeLocation(FVector({0.0f, 0.0f, 3.0f, 1.0f}));
	//StageRenderer->SetupAttachment(RootComponent);

	//FrontBackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
	//FrontBackgroundRenderer->SetSprite("Stage", 3);
	//FrontBackgroundRenderer->SetAutoScaleRatio(3.0f);
	//FrontBackgroundRenderer->SetRelativeLocation(FVector({ 0.0f, 0.0f, 1.0f, 1.0f }));
	//FrontBackgroundRenderer->SetupAttachment(RootComponent);
}

void AStage::BeginPlay()
{
	AActor::BeginPlay();
}

void AStage::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

