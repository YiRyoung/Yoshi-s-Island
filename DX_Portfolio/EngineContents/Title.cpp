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
	BackgroundRenderer->CreateAnimation("Start", "Title", 0, 127, 0.14f);
	{
		USpriteRenderer::FrameAnimation* Animation = BackgroundRenderer->FindAnimation("Start");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 3.0f;
	}

	BackgroundRenderer->ChangeAnimation("Start");
	BackgroundRenderer->SetRelativeLocation({ 0.0f, 660.0 * -0.5f, 0.0f });
	BackgroundRenderer->SetupAttachment(RootComponent);

	UEngineSprite::CreateSpriteToMeta("TitleLogo.png", ".sdata");
	LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();
	LogoRenderer->SetSprite("TitleLogo.png", 0);
	LogoRenderer->SetRelativeScale3D({ 540.0f, 216.0f, 1.0f });
	LogoRenderer->SetRelativeLocation({ -260.0f, 50.0f, 0 });
	LogoRenderer->SetupAttachment(RootComponent);
}

ATitle::~ATitle()
{
}

void ATitle::EndAnimation()
{
	BackgroundRenderer->CreateAnimation("End", "Title", EndAnimIndex, 0, 0.03f, false);
	{
		USpriteRenderer::FrameAnimation* Animation = BackgroundRenderer->FindAnimation("End");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 3.0f;
	}

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
