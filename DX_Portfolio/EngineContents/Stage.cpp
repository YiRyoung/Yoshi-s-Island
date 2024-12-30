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

void AStage::SetBackground(int _Index, FVector _Scale, FVector _Pos)
{
	BackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BackgroundRenderer->SetSprite("Stage", _Index);
	BackgroundRenderer->SetRelativeScale3D(_Scale);
	BackgroundRenderer->SetRelativeLocation(_Pos);
	BackgroundRenderer->SetupAttachment(RootComponent);
}

void AStage::BeginPlay()
{
	AActor::BeginPlay();
}

void AStage::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

