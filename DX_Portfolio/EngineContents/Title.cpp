#include "PreCompile.h"
#include "Title.h"
#include <EngineBase/EngineDebug.h>

#include <EnginePlatform/EngineInput.h>

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/DefaultSceneComponent.h>

ATitle::ATitle()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	BackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
	BackgroundRenderer->SetupAttachment(RootComponent);
	BackgroundRenderer->SetAutoScaleRatio(3.0f);
	BackgroundRenderer->SetRelativeLocation({ 0.0f, 660.0 * -0.5f, 0.0f });
	BackgroundRenderer->CreateAnimation("Start", "Title", 0, 127, 0.14f);
	BackgroundRenderer->ChangeAnimation("Start");

	UEngineSprite::CreateSpriteToMeta("TitleLogo.png", ".sdata");
	LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();
	LogoRenderer->SetupAttachment(RootComponent);
	LogoRenderer->SetRelativeLocation({ -260.0f, 50.0f, 0.0f });
	LogoRenderer->SetSprite("TitleLogo.png", 0);
}

ATitle::~ATitle()
{
}

void ATitle::EndAnimation()
{
	BackgroundRenderer->CreateAnimation("End", "Title", EndAnimIndex, 0, 0.03f, false);
	BackgroundRenderer->ChangeAnimation("End");
}

void ATitle::BeginPlay()
{
	AActor::BeginPlay();
}

void ATitle::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	UEngineDebug::OutPutString("CurIndex : " + std::to_string(BackgroundRenderer->GetCurIndex()));
	UEngineDebug::OutPutString("EndIndex : " + std::to_string(EndAnimIndex));
}
