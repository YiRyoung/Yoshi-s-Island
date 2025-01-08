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

	LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();
	LogoRenderer->SetTexture("TitleLogo.png");
	LogoRenderer->SetScale3D({ 540, 216, 1 });
	LogoRenderer->SetRelativeLocation({ 0.0f, 150.0f, -1.0f });
	LogoRenderer->SetupAttachment(RootComponent);
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
